# Zajecia 7 japierdole jak mnie łeb napierdala uuaauuaa
## co to jest rekurencja???
Rekurencja to przywoływanie samej siebie 

### Prosty Przykład:
```cpp
void odliczanie(int n) {
    if (n <= 0) {  // warunek końcowy
        cout << "Start!";
        return;
    }
    cout << n << "... ";
    odliczanie(n-1);  // funkcja wywołuje samą siebie
}
```

## Kiedy używamy rekurencji? 🎯

1. Gdy problem można podzielić na mniejsze, podobne problemy
2. Gdy rozwiązanie ma naturalną strukturę rekurencyjną

## Przykład: Anagramy 📝

Anagramy to przestawione litery słowa. Rekurencja świetnie się do tego nadaje!

```cpp
void znajdzAnagramy(string slowo, int poczatek, int koniec) {
    if (poczatek == koniec) {
        cout << slowo << endl;  // znaleźliśmy jeden anagram
        return;
    }
    
    for (int i = poczatek; i <= koniec; i++) {
        swap(slowo[poczatek], slowo[i]);  // zamieniamy litery
        znajdzAnagramy(slowo, poczatek + 1, koniec);  // rekurencja!
        swap(slowo[poczatek], slowo[i]);  // przywracamy
    }
}
```

## Rekurencyjne Sortowanie Binarne (QuickSort) 🔄

Wyobraź sobie, że porządkujesz karty:
1. Wybierasz jedną kartę (pivot)
2. Dzielisz pozostałe na dwie grupy: mniejsze i większe
3. Powtarzasz to dla każdej grupy

```cpp
void quickSort(int arr[], int lewy, int prawy) {
    if (lewy < prawy) {
        int pivot = podziel(arr, lewy, prawy);
        
        quickSort(arr, lewy, pivot - 1);    // sortuje od lewa
        quickSort(arr, pivot + 1, prawy);   // sortuje od prawa
    }
}
```

## Ważne Zasady! ⚠️

1. Zawsze We need to put on this thing **warunku końcowego** (base case)
2. Każde wywołanie rekurencyjne powinno przybliżać nas do warunku końcowego, gorzej gdyby było inaczej ale generalnie problem jest taki ze czasem mozna sieknąc zły znak -/+ i bedzie źle 
3. Uważaj na głębokość rekurencji(lepiej unikać dna bo możesz spotkać dolate) - może wyczerpać pamięć stosu/*stack*!

## Zalety i Wady 📊

### Zalety ✅
- Czytelny kod
- Naturalne rozwiązanie dla niektórych problemów
- Eleganckie rozwiązania

### Wady ❌
- Może zużywać dużo pamięci/ napewno tak bedzie 
- Czasami wolniejsza niż rozwiązania iteracyjne
- Może być trudna do zrozumienia na początku
