# ZAJECIA 8 ALGORIYTMY I STRUKTURY DANYCH


## Algorytm `QUICKSORT`
Quicksort to popularny i zazwyczaj bardzo szybki algorytm sortowania. Jego główna idea to *"dziel i zwyciężaj"*.

### 1. **Główna Idea: Dziel i Zwyciężaj**

Wyobraź sobie, że masz talię kart do posortowania. Zamiast przeglądać je wszystkie naraz, robisz tak:

1.  **Dzielisz (Divide):** Wybierasz jedną kartę (nazwijmy ją **pivot**). Przekładasz talię tak, aby wszystkie karty *mniejsze* od pivota były po jednej stronie, a *większe* (lub równe) po drugiej. Pivot ląduje gdzieś pośrodku.
2.  **Zwyciężaj (Conquer):** Masz teraz dwie mniejsze kupki kart (jedną z mniejszymi, drugą z większymi). Sortujesz *każdą z tych kupek osobno*, stosując dokładnie tę samą metodę (dziel i zwyciężaj).
3.  **Połącz (Combine):** W Quicksort ten krok jest trywialny. Gdy posortujesz obie kupki, cała talia jest już posortowana, bo pivot był na właściwym miejscu, mniejsze są przed nim, a większe za nim.

### 2. Kluczowe Kroki w Algorytmie

#### a) Wybór Pivota

*   To element, względem którego będziemy dzielić tablicę.
*   **Jak wybrać?** Można różnie:
    *   Pierwszy element tablicy.
    *   Ostatni element tablicy (często w przykładach).
    *   Środkowy element.
    *   Losowy element.
    *   Mediana z trzech (pierwszego, środkowego, ostatniego - pomaga unikać najgorszego przypadku).
*   Na razie załóżmy, że wybieramy **ostatni** element jako pivot.

```plaintext
Tablica: [7, 2, 1, 6, 8, 5, 3, 4]
Pivot: 4 (ostatni element)
```

#### b) Partycjonowanie (Partitioning) - Serce Algorytmu!

*   **Cel:** Przestawić elementy w tablicy (lub jej fragmencie) tak, aby:
    1.  Pivot znalazł się na swojej *ostatecznej, posortowanej pozycji*.
    2.  Wszystkie elementy mniejsze od pivota były na lewo od niego.
    3.  Wszystkie elementy większe (lub równe) od pivota były na prawo od niego.
*   **Jak to zrobić (koncepcyjnie)?**
    *   Używamy dwóch "wskaźników" lub "markerów". Jeden (`i`) startuje przed początkiem fragmentu, drugi (`j`) na jego końcu (przed pivotem).
    *   Przesuwamy `i` w prawo, aż znajdzie element `>= pivot`.
    *   Przesuwamy `j` w lewo, aż znajdzie element `<= pivot`.
    *   Jeśli `i < j`, zamieniamy miejscami elementy `tablica[i]` i `tablica[j]`.
    *   Powtarzamy, aż `i >= j`.
    *   Na koniec zamieniamy element `tablica[i]` z pivotem. Pozycja `i` jest teraz ostateczną pozycją pivota.
*   **Wynik Partycjonowania dla przykładu:**

```plaintext
Tablica przed: [7, 2, 1, 6, 8, 5, 3, 4]  (Pivot = 4)
Tablica po partycjonowaniu: [3, 2, 1]  4  [8, 5, 6, 7]  (Kolejność w podtablicach nie musi być idealna)
                            ^mniejsze   ^pivot   ^większe/równe

Funkcja partycjonująca zwraca indeks, na którym stanął pivot (tutaj: 3).
```

*   *Fragment kodu :*
    ```cpp
    // Pseudokod uproszczonej pętli partycjonowania
    int i = start - 1;
    int j = koniec; // Zakładając, że pivot jest na 'koniec'

    while (true) {
        // Znajdź element >= pivot od lewej
        while (tablica[++i] < pivot);

        // Znajdź element <= pivot od prawej
        while (j > start && tablica[--j] > pivot);

        if (i >= j) {
            break; // Markery się spotkały lub minęły
        } else {
            swap(tablica[i], tablica[j]); // Zamień znalezione elementy
        }
    }
    swap(tablica[i], tablica[koniec]); // Umieść pivot na właściwym miejscu (i)
    return i; // Zwróć indeks pivota
    ```

#### c) Rekurencja

*   Po partycjonowaniu mamy pivot na swoim miejscu i dwie podtablice.
*   Teraz **wywołujemy Quicksort ponownie** dla tych dwóch podtablic:
    1.  Dla lewej podtablicy (od `start` do `indeks_pivota - 1`).
    2.  Dla prawej podtablicy (od `indeks_pivota + 1` do `koniec`).

*   *Fragment kodu (idea):*
    ```cpp
    void quickSort(int tablica[], int start, int koniec) {
        if (start < koniec) { // Warunek bazowy (czy jest co sortować?)
            // 1. Wybierz pivot (np. ostatni)
            // 2. Podziel tablicę
            int pivotIndex = partition(tablica, start, koniec);

            // 3. Wywołaj rekurencyjnie dla podtablic
            quickSort(tablica, start, pivotIndex - 1);  // Lewa część
            quickSort(tablica, pivotIndex + 1, koniec); // Prawa część
        }
        // Jeśli start >= koniec, podtablica ma 0 lub 1 element -> jest posortowana!
    }
    ```

### 3. Warunek Bazowy Rekurencji

*   Rekurencja musi się kiedyś skończyć!
*   Quicksort przestaje się wywoływać dla danej podtablicy, gdy ma ona **0 lub 1 element** (`start >= koniec`). Taka tablica jest już z definicji posortowana.

### 4. Przykład Krok po Kroku (Bardzo Prosty)

Sortujemy `[5, 1, 4, 2, 8]`

1.  **`quickSort([5, 1, 4, 2, 8], 0, 4)`**
    *   Pivot: `8` (ostatni)
    *   Partycjonowanie: Wskaźniki `i` i `j` szukają elementów do zamiany. Po przestawieniu pivot `8` ląduje na końcu, bo jest największy. Wynik: `[5, 1, 4, 2] 8`. Indeks pivota: `4`.
    *   Wywołania rekurencyjne:
        *   `quickSort([5, 1, 4, 2], 0, 3)`
        *   `quickSort([], 5, 4)` -> Koniec (warunek bazowy `start >= koniec`)

2.  **`quickSort([5, 1, 4, 2], 0, 3)`**
    *   Pivot: `2` (ostatni)
    *   Partycjonowanie: Wynik: `[1] 2 [4, 5]`. Indeks pivota: `1`.
    *   Wywołania rekurencyjne:
        *   `quickSort([1], 0, 0)` -> Koniec (warunek bazowy)
        *   `quickSort([4, 5], 2, 3)`

3.  **`quickSort([4, 5], 2, 3)`**
    *   Pivot: `5` (ostatni)
    *   Partycjonowanie: Wynik: `[4] 5`. Indeks pivota: `3`.
    *   Wywołania rekurencyjne:
        *   `quickSort([4], 2, 2)` -> Koniec (warunek bazowy)
        *   `quickSort([], 4, 3)` -> Koniec (warunek bazowy)

Wszystkie podproblemy rozwiązane, wracamy w górę rekurencji. Ostateczny wynik: `[1, 2, 4, 5, 8]`.

### Podsumowanie

*   Quicksort to rekurencyjny algorytm sortowania.
*   Dzieli problem na mniejsze podproblemy przez **partycjonowanie** wokół **pivota**.
*   Kluczem jest umieszczenie pivota na właściwym miejscu i podział reszty na mniejsze/większe.
*   Kończy działanie, gdy podtablice mają 0 lub 1 element.
*   Jest szybki w *średnim* przypadku ($O(n log n)$), ale *może* być wolny w najgorszym ($O(n^2)$), np. gdy tablica jest już posortowana i wybieramy zawsze pierwszy/ostatni element jako pivot.


## Improved Quicksort

*Super Quicksort - Jeszcze Lepsze Sortowanie Zabawek!*

Hej! Pamiętasz zwykły Quicksort? Mieliśmy "szefa" (pivot) i dzieliliśmy zabawki.
- Ten jest **ulepszony** i działa **szybciej**, zwłaszcza jak czasem trafi się słaby podział! Ma dwa super triki(rozkminki), które sprawiają, że działa lepiej:

## 1. Mądrzejszy Wybór Szefa (Pivota) 🧠

*   **Problem:** Czasem stary Quicksort wybierał na szefa największą lub najmniejszą zabawkę, co spowalniało sortowanie.
*   **Rozwiązanie:** Patrzymy na **trzy** zabawki (pierwszą, środkową, ostatnią). Wybieramy tę **"w sam raz"** (środkową co do wielkości) na szefa!
*   **Jak w kodzie?** Funkcja `medianOf3` znajduje tego "średniego" kandydata i ustawia go jako pivot.
    ```cpp
    // W recQuickSort, gdy kupa jest duża:
    double median = medianOf3(left, right); // Znajdź mądrego szefa
    int partition = partitionIt(left, right, median); // Podziel używając go
    ```
*   **Po co?** Lepszy szef = bardziej równy podział kupki = szybsze sortowanie! 🎉

## 2. Małe Kupki Sortujemy Prościej 👍

*   **Problem:** Używanie skomplikowanego Quicksorta dla 2-3 zabawek to strata czasu.
*   **Rozwiązanie:** Jeśli kupka jest **malutka** (3 zabawki lub mniej), sortujemy ją **"ręcznie"** - po prostu porównujemy te kilka zabawek i ustawiamy w kolejności.
*   **Jak w kodzie?** `recQuickSort` najpierw sprawdza rozmiar kupki. Jak mała, woła `manualSort`.
    ```cpp
    // Na początku recQuickSort:
    int size = right-left+1;
    if(size <= 3) {
       manualSort(left, right); // Proste sortowanie dla małych!
    } else {
       // ... normalny Quicksort z mądrym szefem ...
    }
    ```
    A `manualSort` po prostu robi kilka porównań i zamian dla 2 lub 3 elementów.
*   **Po co?** Dla małych kupek to dużo szybsze niż cała maszyna Quicksorta! 🚀

**Dzięki tym dwóm trikom nasz Super Quicksort jest sprytniejszy i często szybszy niż ten zwykły!**


# Smartpointery w QUICKSORT
## Jak Zastosować Mądre Wskaźniki w Naszym Quicksort?
W naszym przykładzie `quickSort2.cpp` mamy klasę `ArrayIns`, która w środku używa `std::vector<double> theVect;`.

**Ważna sprawa:** Sam `std::vector` jest już bardzo "mądry"! On *sam* zarządza swoją pamięcią. Jak dodajesz elementy, on sam powiększa swoje miejsce w pamięci. Jak `vector` znika, on sam sprząta po sobie. **Więc NIE potrzebujemy mądrych wskaźników do zarządzania pamięcią *wewnątrz* `std::vector<double>`!**

Ale **możemy** użyć mądrego wskaźnika do zarządzania **samym obiektem `ArrayIns`**, który tworzymy w funkcji `main`.

Popatrz na `main` w poprzednim kodzie:

```cpp
int main() {
    int maxSize = 16;
    ArrayIns arr(maxSize); // <--- arr jest tworzone "normalnie" (na stosie)

    // ... używamy arr.insert(), arr.display(), arr.quickSort() ...

    return 0; // <-- Tutaj 'arr' jest automatycznie niszczone, bo kończy się jego zasięg
}
```

Tutaj `arr` jest obiektem na stosie. Jest tworzone na początku `main` i automatycznie niszczone na końcu. To jest proste i bezpieczne w tym przypadku.

Ale gdybyśmy z jakiegoś powodu *musieli* stworzyć `arr` dynamicznie na stercie (używając `new`), wtedy mądry wskaźnik byłby superbohaterem!

**Przykład (teoretyczny, bo tu nie jest konieczny, ale pokazuje ideę):**

```cpp
#include <memory> // Potrzebujemy tego pliku do mądrych wskaźników!

int main() {
    int maxSize = 16;

    // === Użycie mądrego wskaźnika ===
    // Zamiast: ArrayIns* arr_ptr_raw = new ArrayIns(maxSize);
    // Robimy:
    std::unique_ptr<ArrayIns> arr_ptr = std::make_unique<ArrayIns>(maxSize);
    // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    // To tworzy ArrayIns na stercie i od razu daje wskaźnik pod opiekę unique_ptr.
    // Używamy std::make_unique - to najlepszy sposób tworzenia unique_ptr.

    std::cout << "Zabawki przed sortowaniem:" << std::endl;
    // Używamy operatora -> zamiast . bo mamy wskaźnik (nawet jeśli mądry)
    arr_ptr->display();
    std::cout << std::endl;

    // Wkładamy zabawki (używając ->)
    srand(time(NULL));
    for(int j=0; j<maxSize; j++) {
       double n = rand() % 100;
       arr_ptr->insert(n); // Używamy ->
    }

     std::cout << "Po włożeniu zabawek:" << std::endl;
     arr_ptr->display(); // Używamy ->
     std::cout << std::endl;

    // Wywołujemy sortowanie (używając ->)
    arr_ptr->quickSort(); // Używamy ->

    std::cout << std::endl;
    std::cout << "Zabawki po sortowaniu:" << std::endl;
    arr_ptr->display(); // Używamy ->

    return 0;
    // === MAGIA MĄDREGO WSKAŹNIKA ===
    // Tutaj 'arr_ptr' wychodzi z zasięgu.
    // unique_ptr WIDZI TO i AUTOMATYCZNIE woła 'delete' na obiekt ArrayIns,
    // który trzymał! Nie musimy pisać 'delete arr_ptr_raw;'! Super!
}

```


## Dodatkowy Tip: Mądre Wskaźniki (Smart Pointers) 🧠💡

W C++ mamy coś takiego jak **mądre wskaźniki** (np. `std::unique_ptr`, `std::shared_ptr`). To jak specjalne pudełka na zwykłe wskaźniki (`*`), które **same pamiętają o sprzątaniu** (wołaniu `delete`)!

*   **Po co?** Żeby uniknąć błędów i zapominania o `delete`, co prowadzi do bałaganu w pamięci (wycieków).
*   **Jak działają?** Gdy mądry wskaźnik (pudełko) przestaje być potrzebny, automatycznie niszczy obiekt, na który wskazywał.
*   **W naszym Quicksort:**
    *   **WAŻNE:** Nie potrzebujemy ich do zarządzania pamięcią *wewnątrz* `std::vector<double>`, bo `vector` już jest mądry i sam to robi!
    *   **ALE:** Moglibyśmy użyć `std::unique_ptr` do zarządzania **całym obiektem `ArrayIns`**, gdybyśmy tworzyli go dynamicznie przez `new` w funkcji `main`.

    ```cpp
    #include <memory> // Potrzebny plik

    // Zamiast: ArrayIns* arr_ptr_raw = new ArrayIns(maxSize);
    // I potem pamiętać o: delete arr_ptr_raw;

    // Można zrobić:
    std::unique_ptr<ArrayIns> arr_ptr = std::make_unique<ArrayIns>(maxSize);

    // I używać go przez ->
    arr_ptr->display();
    arr_ptr->insert(10.0);
    // ... itd.

    // Kiedy arr_ptr zniknie, obiekt ArrayIns zostanie AUTOMATYCZNIE usunięty!
    // Nie trzeba pisać delete!
    ```
*   **Wniosek:** Mądre wskaźniki są super do zarządzania dynamicznie alokowaną pamięcią, ale używaj ich tam, gdzie są potrzebne (głównie zamiast surowych wskaźników z `new`/`delete`).



