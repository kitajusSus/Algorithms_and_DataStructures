
# Inteligentne Wskaźniki (Smart Pointers) w C++ 

## Po co to w ogóle? Problem z `new` i `delete`

Pamiętasz `new` i `delete`? Super, ale łatwo coś spieprzyć:
- **Zapomnisz `delete`** -> wyciek pamięci (memory leak), apka zżera RAM jak głupia.
- **Zrobisz `delete` dwa razy** na tym samym -> crash, albo inne dziwne akcje (undefined behavior).
- **Zrobisz `delete` na złym wskaźniku** (np. ze stosu) -> crash.
- **Wyjątek poleci gdzieś w funkcji** zanim zdążysz zrobić `delete` -> wyciek pamięci.

Ręczne zarządzanie pamięcią jest **upierdliwe i ryzykowne**.

## Rozwiązanie: Inteligentne Wskaźniki!

To są takie **sprytne klasy**, które opakowują zwykły ("surowy") wskaźnik (`Typ*`). Działają na zasadzie **RAII** (Resource Acquisition Is Initialization) - czyli "zasób jest łapany przy inicjalizacji".

**Jak to działa (w skrócie):**
1.  Tworzysz inteligentny wskaźnik, dajesz mu wskaźnik z `new` (albo używasz `make_unique`/`make_shared`). Inteligentny wskaźnik **przejmuje własność** tego surowego wskaźnika.
2.  Używasz inteligentnego wskaźnika jak zwykłego (ma przeciążone `*` i `->`).
3.  Kiedy inteligentny wskaźnik **kończy swoje życie** (np. zmienna lokalna wychodzi poza `{}`), jego **destruktor SAM AUTOMATYCZNIE woła `delete`** (albo `delete[]`) na tym surowym wskaźniku.

**Co nam to daje? Czemu to jest cool?**
- ✅ **Koniec z pamiętaniem o `delete`!** Samo się robi.
- ✅ **Bezpieczne przy wyjątkach:** Nawet jak poleci wyjątek, destruktor inteligentnego wskaźnika się wywoła i posprząta.
- ✅ **Mniej wycieków pamięci.**
- ✅ **Jasne kto jest właścicielem pamięci** (kto jest odpowiedzialny za zwolnienie).

## Główne Typy Inteligentnych Wskaźników (z `<memory>`)

### 1. `std::unique_ptr<T>` (Unikalny Właściciel)

- **Własność:** **Wyłączna** (unique). Tylko **jeden** `unique_ptr` może w danym momencie "posiadać" obiekt. Jak samotny wilk.
- **Kopiowanie:** **ZABRONIONE**. Nie skopiujesz go, bo wtedy byłoby dwóch właścicieli.
- **Przenoszenie:** **DOZWOLONE** (`std::move()`). Możesz przekazać własność innemu `unique_ptr`. Stary staje się pusty (`nullptr`).
- **Wydajność:** **Szybki jak błyskawica**. Zwykle zero dodatkowego kosztu w porównaniu do surowego wskaźnika.
- **Kiedy używać:** **PRAWIE ZAWSZE!** To powinien być Twój domyślny wybór, jeśli potrzebujesz wskaźnika na obiekt na stercie, a nie musisz go współdzielić.
- **Jak tworzyć:** Używaj `std::make_unique<T>(argumenty)` (od C++14). Bezpieczniejsze i czasem szybsze.

```cpp
// Tworzenie
std::unique_ptr<MyClass> u_ptr1 = std::make_unique<MyClass>(10);

// Używanie
u_ptr1->doSomething();

// std::unique_ptr<MyClass> u_ptr2 = u_ptr1; // BŁĄD! Nie skopiujesz.

// Przeniesienie własności
std::unique_ptr<MyClass> u_ptr3 = std::move(u_ptr1); // OK, teraz u_ptr3 ma obiekt, a u_ptr1 jest pusty (nullptr)

// u_ptr3 samo posprząta jak wyjdzie poza zakres
```

### 2. `std::shared_ptr<T>` (Współdzielony Właściciel)

- **Własność:** **Współdzielona** (shared). Wiele `shared_ptr` może wskazywać na **ten sam** obiekt. Jak impreza, wszyscy mają dostęp.
- **Jak to działa:** Używa **licznika referencji**. Każdy `shared_ptr` wskazujący na obiekt zwiększa licznik. Kiedy `shared_ptr` jest niszczony, zmniejsza licznik. Obiekt jest usuwany (`delete`) dopiero, gdy **licznik spadnie do zera**.
- **Kopiowanie:** **DOZWOLONE**. Kopiowanie zwiększa licznik referencji.
- **Przenoszenie:** **DOZWOLONE**. Przenoszenie nie zmienia licznika.
- **Wydajność:** Ma **mały narzut** (dodatkowa pamięć na licznik, atomowe operacje na liczniku - ważne przy wątkach). Trochę wolniejszy niż `unique_ptr`.
- **Kiedy używać:** Gdy **wiele niezależnych części kodu** musi mieć dostęp do tego samego obiektu i nie wiadomo, która skończy go używać jako ostatnia. Uwaga na **cykle referencji**! (patrz `weak_ptr`).
- **Jak tworzyć:** Używaj `std::make_shared<T>(argumenty)`. Wydajniejsze (jedna alokacja na obiekt i licznik) i bezpieczniejsze przy wyjątkach.

```cpp
// Tworzenie
std::shared_ptr<MyClass> s_ptr1 = std::make_shared<MyClass>(20);
std::cout << "Licznik: " << s_ptr1.use_count() << std::endl; // Pokazuje 1

// Kopiowanie
std::shared_ptr<MyClass> s_ptr2 = s_ptr1; // OK, teraz dwa wskazują na obiekt
std::cout << "Licznik: " << s_ptr1.use_count() << std::endl; // Pokazuje 2

{
    std::shared_ptr<MyClass> s_ptr3 = s_ptr1; // Kolejna kopia
    std::cout << "Licznik: " << s_ptr1.use_count() << std::endl; // Pokazuje 3
} // s_ptr3 wychodzi poza zakres, destruktor zmniejsza licznik

std::cout << "Licznik: " << s_ptr1.use_count() << std::endl; // Pokazuje 2

// Pamięć zostanie zwolniona, gdy ostatni shared_ptr (s_ptr1 lub s_ptr2) zniknie
```

### 3. `std::weak_ptr<T>` (Obserwator Bez Własności)

- **Własność:** **ŻADNA**. To jest "słaby" wskaźnik. On tylko **obserwuje** obiekt zarządzany przez `shared_ptr`, ale **nie zwiększa licznika referencji**. Nie trzyma obiektu przy życiu.
- **Po co to komu?** Głównie do **przerywania cykli referencji** w `shared_ptr`. Przykład: Obiekt A ma `shared_ptr` do B, a B ma `shared_ptr` do A. Nigdy licznik nie spadnie do zera, nawet jak nic innego ich nie używa -> wyciek! Jeśli B ma `weak_ptr` do A, cykl jest przerwany.
- **Jak używać:** Nie da się go bezpośrednio użyć (`->`, `*`). Trzeba go najpierw "zamknąć" (zamienić na `shared_ptr`) metodą `lock()`.
    - `lock()` zwraca `shared_ptr`:
        - Jeśli obiekt **jeszcze istnieje**, dostajesz ważny `shared_ptr` (licznik rośnie o 1 na czas życia tego tymczasowego `shared_ptr`).
        - Jeśli obiekt **już został usunięty**, dostajesz pusty `shared_ptr` (`nullptr`).

```cpp
std::shared_ptr<MyClass> sp = std::make_shared<MyClass>(30);
std::weak_ptr<MyClass> wp = sp; // wp obserwuje obiekt sp, licznik bez zmian

// ...gdzieś indziej w kodzie...

// Próba uzyskania dostępu
if (std::shared_ptr<MyClass> temp_sp = wp.lock()) {
    // Udało się! Obiekt istnieje, temp_sp go teraz trzyma (licznik +1)
    std::cout << "Obiekt istnieje, używam..." << std::endl;
    temp_sp->doSomething();
    // temp_sp zaraz zniknie, licznik wróci do normy
} else {
    // Nie udało się, obiekt został już usunięty
    std::cout << "Obiekt już nie istnieje." << std::endl;
}
```

## Podsumowanie / TL;DR

> - **Używaj inteligentnych wskaźników zamiast gołych `new`/`delete`!** To bezpieczniejsze i wygodniejsze.
> - **`std::unique_ptr` to Twój najlepszy kumpel** - używaj go domyślnie. Jest szybki i ma jasną własność.
> - **`std::shared_ptr`** gdy naprawdę potrzebujesz **współdzielić własność** obiektu między różnymi częściami kodu. Pamiętaj o małym narzucie i ryzyku cykli.
> - **`std::weak_ptr`** głównie do **przerywania cykli** w `shared_ptr`.
> - Zawsze staraj się używać **`std::make_unique`** i **`std::make_shared`** do tworzenia.

Zapomnij o ręcznym `delete` (w większości przypadków)! Niech RAII i inteligentne wskaźniki robią robotę za Ciebie. 😎
