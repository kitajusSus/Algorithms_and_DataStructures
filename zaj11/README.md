


# Algorytmy i Struktury Danych – Kopiec (Heap) dla Opornych (i Malutkich!)

Hej! 

Dzisiaj pobawimy się w coś super fajnego, co nazywa się **Kopiec** (po angielsku *Heap*, a niektórzy mówią też *sterta*). Wyobraź sobie, że masz górę zabawek, ale nie byle jaką! Ta góra ma specjalne zasady.

## Plan Wykładu (czyli co będziemy dzisiaj robić):

1.  **Kopiec** – Co to w ogóle jest? (jak ta specjalna góra zabawek)
2.  **Wprowadzenie** – Jakie są rodzaje kopców?
3.  **Przykłady implementacji** – Do czego to się przydaje? (np. kolejka do lekarza dla VIP-ów)
4.  **Kopiec oparty na drzewie (i tablicy!)** – Jak to jest zbudowane w środku?
5.  **Heapsort** – Jak posortować zabawki używając kopca?

---

## 1. Kopiec – Co to takiego?

Wyobraź sobie kopiec piasku albo górę klocków. W informatyce Kopiec to taka sprytna struktura danych, która wygląda trochę jak drzewo (takie do góry nogami), ale ma specjalne zasady:

*   **Kopiec MAX (Max-Heap):** Największy klocek (liczba) jest zawsze na samej górze (w korzeniu). A każdy rodzic jest większy (lub równy) od swoich dzieci. Jak tatuś miś, który jest większy od swoich małych misiów.
    *   Na slajdzie 3 masz przykład: 55 jest na górze, a pod nim są mniejsze liczby (44, 24). A 44 jest większe od 21 i 32.
*   **Kopiec MIN (Min-Heap):** Działa odwrotnie. Najmniejszy klocek jest na górze. Każdy rodzic jest mniejszy (lub równy) od swoich dzieci.

**Zasada główna kopca (dla Max-Heap):**
`Klocek_Dziecka <= Klocek_Rodzica`
(Na slajdzie 3: `Array[i] <= Array[Rodzic[i]]`)

---

## 2. Jak to jest zbudowane w środku? Magia tablicy!

Mimo że kopiec wygląda jak drzewo, to w komputerze najczęściej trzymamy go w zwykłej tablicy (takiej liście numerków). To jest super sprytne!

Popatrz na slajd 3:
Drzewo:
```
      55 (indeks 0 w tablicy)
     /  \
   44    24 (indeksy 1, 2)
  / \   / \
21  32 19  3 (indeksy 3, 4, 5, 6)
/ \
7  18 (indeksy 7, 8)
```
Tablica: `[55, 44, 24, 21, 32, 19, 3, 7, 18]` (indeksy od 0 do 8)

**Jak znaleźć rodzica i dzieci w tablicy (jeśli indeksujemy od 0)?**
Załóżmy, że jakiś element jest na pozycji `i` w tablicy:

*   **Rodzic elementu `i`:** jest na pozycji `(i - 1) / 2` (dzielenie całkowite, czyli bez reszty)
*   **Lewe dziecko elementu `i`:** jest na pozycji `2 * i + 1`
*   **Prawe dziecko elementu `i`:** jest na pozycji `2 * i + 2`

**Przykład ze slajdu 3 (indeksowanie od 0):**
Weźmy `32` (jest na indeksie `i = 4`).
*   Rodzic `32`: `(4 - 1) / 2 = 3 / 2 = 1`. Na indeksie 1 jest `44`. Zgadza się!
Weźmy `44` (jest na indeksie `i = 1`).
*   Lewe dziecko `44`: `2 * 1 + 1 = 3`. Na indeksie 3 jest `21`. Zgadza się!
*   Prawe dziecko `44`: `2 * 1 + 2 = 4`. Na indeksie 4 jest `32`. Zgadza się!

*Uwaga: Na slajdach wzory są podane dla indeksowania od 1 (`floor(i/2)`, `2*i`, `2*i+1`). W C++ częściej używamy indeksowania od 0, więc powyższe wzory są dla C++.*

---

## 3. Do czego to się przydaje? Kolejka Priorytetowa! (Slajd 4)

Kopiec jest super do robienia **kolejek priorytetowych**. Wyobraź sobie kolejkę w szpitalu:
*   Ktoś z zawałem serca (wysoki priorytet) powinien być obsłużony przed kimś ze złamanym palcem (niższy priorytet).
*   Kopiec Max może trzymać pacjentów, gdzie "największy" priorytet jest zawsze na górze i gotowy do obsłużenia.
*   Kopiec Min może trzymać zadania, gdzie "najmniejszy" koszt (np. czas wykonania) jest na górze.

**Główne operacje w kolejce priorytetowej (i na kopcu):**
*   **Dodawanie nowego elementu** (np. nowy pacjent przychodzi) - `insertion (pushing)`
*   **Znajdowanie elementu o najwyższym/najniższym priorytecie** (kto jest następny?) - to zawsze ten na górze kopca!
*   **Usuwanie elementu o najwyższym/najniższym priorytecie** (obsłużyliśmy pacjenta) - `deleting (popping)`

---

## 4. Operacje na Kopcu – Krok po Kroku

### A. Dodawanie nowego elementu (Pushing a new item) – Slajdy 6-8

Powiedzmy, że mamy Max-Heap i chcemy dodać `48`.

1.  **Dodaj na koniec:** Wrzucamy nowy element na sam koniec tablicy (czyli na pierwsze wolne miejsce na najniższym poziomie drzewa, od lewej).
    *   Slajd 6: `48` ląduje na końcu. Tablica: `[55, 44, 24, 21, 32, 19, 3, 7, 18, 48]`
2.  **Napraw kopiec "do góry" (Sift-up / Przesiewanie w górę):**
    *   Nowy element (`48`) może być większy od swojego rodzica (`21`). Jeśli tak jest, to łamiemy zasadę kopca Max!
    *   Musimy zamienić miejscami `48` z jego rodzicem `21`.
        *   Slajd 7: `48` zamienia się z `21`.
    *   Teraz `48` jest wyżej. Sprawdzamy znowu: czy `48` jest większy od swojego nowego rodzica (`44`)? Tak!
    *   Zamieniamy `48` z `44`.
        *   Slajd 8: `48` zamienia się z `44`.
    *   Teraz `48` jest jeszcze wyżej. Sprawdzamy: czy `48` jest większy od swojego nowego rodzica (`55`)? Nie, `55` jest większe.
    *   Super! Kopiec jest naprawiony. `48` znalazł swoje miejsce.

**Programik w C++ (dodawanie do Max-Heap):**
```cpp
#include <iostream>
#include <vector>
#include <algorithm> // Dla std::swap

// Funkcje pomocnicze dla tablicy indeksowanej od 0
int parent(int i) { return (i - 1) / 2; }

void siftUp(std::vector<int>& heap, int index) {
    // Dopóki element nie jest korzeniem (indeks > 0)
    // ORAZ jest większy od swojego rodzica
    while (index > 0 && heap[index] > heap[parent(index)]) {
        std::swap(heap[index], heap[parent(index)]);
        index = parent(index); // Idziemy w górę do pozycji rodzica
    }
}

void pushToHeap(std::vector<int>& heap, int value) {
    heap.push_back(value); // Dodaj na koniec
    siftUp(heap, heap.size() - 1); // Napraw od nowego elementu w górę
}

void printHeap(const std::vector<int>& heap) {
    for (int val : heap) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

int main_push_example() { // Zmieniona nazwa, żeby nie kolidowało
    std::vector<int> myHeap = {55, 44, 24, 21, 32, 19, 3, 7, 18};
    std::cout << "Kopiec przed dodaniem 48: ";
    printHeap(myHeap);

    pushToHeap(myHeap, 48);
    std::cout << "Kopiec po dodaniu 48:    ";
    printHeap(myHeap); // Oczekiwany wynik podobny do slajdu 8

    pushToHeap(myHeap, 60);
    std::cout << "Kopiec po dodaniu 60:    ";
    printHeap(myHeap);
    return 0;
}
```

### B. Usuwanie elementu z góry (Poping an item) – Slajdy 9-12

Chcemy usunąć największy element z Max-Heap (czyli ten z korzenia, np. `55`).

1.  **Zapamiętaj korzeń:** Bierzemy wartość z korzenia (`55`) – to jest nasz wynik.
2.  **Przenieś ostatni na górę:** Bierzemy ostatni element z kopca (np. `32` ze slajdu 9, zakładając, że `48` już tam było i zostało poprawnie wstawione, a potem usunęliśmy `55` i `48` i teraz korzeniem jest `55`, a ostatnim `32` z jakiegoś wcześniejszego stanu).
    *   Slajd 9: Mamy kopiec `[55, 48, 24, 21, 44, 19, 3, 7, 18, 32]`. Ostatni to `32`.
    *   Wstawiamy ten ostatni element (`32`) na miejsce korzenia.
    *   Usuwamy ten ostatni element z końca tablicy (kopiec się zmniejsza).
    *   Slajd 10: `32` jest teraz na górze. Tablica (bez starego `32` na końcu): `[32, 48, 24, 21, 44, 19, 3, 7, 18]`
3.  **Napraw kopiec "w dół" (Sift-down / Przesiewanie w dół):**
    *   Nowy korzeń (`32`) może być mniejszy od swoich dzieci (`48` i `24`). To łamie zasadę Max-Heap!
    *   Porównujemy `32` z jego dziećmi. Wybieramy większe dziecko (tutaj `48`).
    *   Jeśli `32` jest mniejsze od większego dziecka (`48`), zamieniamy je miejscami.
        *   Slajd 11: `32` zamienia się z `48`.
    *   Teraz `32` jest niżej. Znowu sprawdzamy jego dzieci (teraz `21` i `44`). Większe jest `44`.
    *   Czy `32` jest mniejsze od `44`? Tak! Zamieniamy.
        *   Slajd 12: `32` zamienia się z `44`.
    *   Teraz `32` jest liściem (nie ma dzieci) albo jest większe od swoich dzieci. Kopiec naprawiony!

**Programik w C++ (usuwanie z Max-Heap):**
```cpp
#include <iostream>
#include <vector>
#include <algorithm> // Dla std::swap
#include <stdexcept> // Dla std::out_of_range

// Funkcje pomocnicze dla tablicy indeksowanej od 0
int parent_pop(int i) { return (i - 1) / 2; } // Uniknięcie redefinicji
int leftChild(int i) { return 2 * i + 1; }
int rightChild(int i) { return 2 * i + 2; }

void siftDown(std::vector<int>& heap, int heapSize, int index) {
    int maxIndex = index; // Zakładamy, że bieżący element jest największy

    int l = leftChild(index);
    // Jeśli lewe dziecko istnieje I jest większe od obecnego maxIndex
    if (l < heapSize && heap[l] > heap[maxIndex]) {
        maxIndex = l;
    }

    int r = rightChild(index);
    // Jeśli prawe dziecko istnieje I jest większe od obecnego maxIndex
    if (r < heapSize && heap[r] > heap[maxIndex]) {
        maxIndex = r;
    }

    // Jeśli największy element nie jest już na pozycji 'index' (czyli rodzicem)
    if (index != maxIndex) {
        std::swap(heap[index], heap[maxIndex]);
        siftDown(heap, heapSize, maxIndex); // Rekurencyjnie naprawiaj w dół
    }
}

int popFromHeap(std::vector<int>& heap) {
    if (heap.empty()) {
        throw std::out_of_range("Kopiec jest pusty!");
    }
    int result = heap[0]; // Zapamiętaj korzeń
    heap[0] = heap.back(); // Ostatni element na miejsce korzenia
    heap.pop_back();      // Usuń ostatni element

    if (!heap.empty()) {
        siftDown(heap, heap.size(), 0); // Napraw kopiec od korzenia w dół
    }
    return result;
}

void printHeap_pop(const std::vector<int>& heap) { // Uniknięcie redefinicji
    for (int val : heap) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}


int main_pop_example() { // Zmieniona nazwa
    // Zaczynamy od kopca ze slajdu 8 (po dodaniu 48)
    std::vector<int> myHeap = {55, 48, 24, 21, 44, 19, 3, 7, 18, 32}; // Po dodaniu 48, a potem 32
    // Ręcznie robię stan podobny do tego, co mogłoby być przed popem na slajdzie 9, ale upraszczam
    // Weźmy kopiec, z którego chcemy usunąć 55. Załóżmy, że ostatnim elementem jest 32.
    myHeap = {55, 48, 24, 21, 44, 19, 3, 7, 18, 32}; // Stan ze slajdu 9 przed operacjami.
                                                 // Ostatnim jest 32.
                                                 // Korzeniem jest 55.
    std::cout << "Kopiec przed usunięciem max: ";
    printHeap_pop(myHeap);

    int maxValue = popFromHeap(myHeap);
    std::cout << "Usunięto: " << maxValue << std::endl;
    std::cout << "Kopiec po usunięciu max:     ";
    printHeap_pop(myHeap); // Powinno być podobne do slajdu 12

    if (!myHeap.empty()) {
        maxValue = popFromHeap(myHeap);
        std::cout << "Usunięto: " << maxValue << std::endl;
        std::cout << "Kopiec po kolejnym usunięciu: ";
        printHeap_pop(myHeap);
    }
    return 0;
}
```

---

## 5. Budowanie Kopca (Function: makeHeap()) – Slajdy 25-36

A co jeśli mamy na początku losową tablicę i chcemy z niej zrobić kopiec?
Na slajdach pokazany jest sposób "Random pushing of new items", czyli traktujemy każdy element po kolei tak, jakbyśmy go dodawali do pustego kopca (czyli `siftUp` dla każdego). To działa, ale jest wolniejsze.

Jest sprytniejszy sposób (`O(N)` zamiast `O(N log N)`):
1.  Zauważ, że wszystkie liście (elementy bez dzieci) już są "mini-kopcami" same w sobie.
2.  Zaczynamy od ostatniego elementu, który NIE jest liściem. W tablicy o rozmiarze `n`, to będzie element na indeksie `(n / 2) - 1`.
3.  Dla tego elementu (i wszystkich wcześniejszych aż do korzenia) wykonujemy operację `siftDown`.

**Programik w C++ (budowanie Max-Heap z tablicy):**
```cpp
#include <iostream>
#include <vector>
#include <algorithm> // Dla std::swap

// Funkcje pomocnicze (leftChild, rightChild, siftDown) są potrzebne - zakładamy, że są zdefiniowane jak wyżej

void buildHeap(std::vector<int>& arr) {
    int n = arr.size();
    // Zaczynamy od ostatniego rodzica i idziemy w górę aż do korzenia
    for (int i = (n / 2) - 1; i >= 0; i--) {
        siftDown(arr, n, i); // Dla każdego rodzica robimy siftDown
    }
}

void printHeap_build(const std::vector<int>& heap) { // Uniknięcie redefinicji
    for (int val : heap) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

int main_build_example() { // Zmieniona nazwa
    std::vector<int> data = {13, 3, 19, 15, 4, 20, 21, 16, 17, 18}; // Dane ze slajdu 25
    std::cout << "Tablica przed budowaniem kopca: ";
    printHeap_build(data);

    buildHeap(data);
    std::cout << "Tablica po zbudowaniu kopca:   ";
    printHeap_build(data); // Powinien być poprawny Max-Heap

    // Możesz teraz użyć popFromHeap, żeby zobaczyć, że działa
    if (!data.empty()) {
        std::cout << "Po pop: " << popFromHeap(data) << std::endl; // popFromHeap i siftDown muszą być dostępne
        printHeap_build(data);
    }
    return 0;
}
```

---

## 6. Heapsort – Sortowanie przez Kopcowanie! – Slajdy 13-23

Jak już mamy Max-Heap, sortowanie jest proste jak drut!

1.  **Zbuduj Max-Heap:** Zrób ze swojej nieposortowanej tablicy Max-Heap (jak w punkcie 5).
    *   Teraz największy element jest na samej górze (na indeksie 0).
2.  **Powtarzaj, aż posortujesz:**
    a.  **Zamień:** Zamień miejscami element z korzenia (największy w pozostałej części kopca) z ostatnim elementem *aktualnego* kopca.
        *   Teraz największy element jest na swoim właściwym, posortowanym miejscu na końcu tablicy!
    b.  **Zmniejsz rozmiar kopca:** Udawaj, że kopiec jest o jeden element mniejszy (ten posortowany na końcu już się nie liczy do kopca).
    c.  **Napraw kopiec:** Element, który trafił na górę (ten z końca), pewnie psuje kopiec. Zrób `siftDown` na korzeniu, żeby go naprawić (ale tylko w tej zmniejszonej części kopca).
3.  Powtarzaj kroki a, b, c, aż rozmiar kopca będzie 1 (albo 0). Tablica będzie posortowana!

Popatrz na slajdy 14-23 – dokładnie to tam się dzieje.
*   Slajd 14: Po `pop` mamy `48` na górze. Ostatni element to `18`.
*   Slajd 15: Zamieniamy `48` (korzeń) z `18` (ostatni). `48` idzie na koniec (już posortowane). `18` idzie na górę. Zmniejszamy rozmiar kopca.
*   Slajdy 16-17: `siftDown` dla `18`. `18` zamienia się z `44`, potem `18` zamienia się z `32`. Kopiec naprawiony (bez `48`).
*   I tak dalej...

**Programik w C++ (Heapsort):**
```cpp
#include <iostream>
#include <vector>
#include <algorithm> // Dla std::swap

// Funkcje pomocnicze (leftChild, rightChild, siftDown, buildHeap) są potrzebne

void heapSort(std::vector<int>& arr) {
    int n = arr.size();

    // 1. Zbuduj Max-Heap z całej tablicy
    buildHeap(arr); // buildHeap używa siftDown, więc potrzebujemy leftChild, rightChild

    // 2. Sortowanie
    // Wykonuj (n-1) razy (ostatni element sam się ustawi)
    for (int i = n - 1; i > 0; i--) {
        // a. Zamień korzeń (największy) z ostatnim elementem aktualnego kopca
        std::swap(arr[0], arr[i]);

        // b. Zmniejsz rozmiar kopca (przekazując 'i' jako nowy rozmiar do siftDown)
        // c. Napraw kopiec na zmniejszonym zakresie
        siftDown(arr, i, 0); // 'i' to nowy rozmiar kopca, bo arr[i] jest już posortowane
    }
}

void printArray_heapsort(const std::vector<int>& arr) { // Uniknięcie redefinicji
    for (int val : arr) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

// Aby to wszystko skompilować razem, musimy zdefiniować wszystkie funkcje w jednym miejscu
// albo użyć plików nagłówkowych. Dla prostoty, skopiuję potrzebne funkcje tutaj:

int parent_hs(int i) { return (i - 1) / 2; }
int leftChild_hs(int i) { return 2 * i + 1; }
int rightChild_hs(int i) { return 2 * i + 2; }

void siftDown_hs(std::vector<int>& heap, int heapSize, int index) {
    int maxIndex = index;
    int l = leftChild_hs(index);
    if (l < heapSize && heap[l] > heap[maxIndex]) {
        maxIndex = l;
    }
    int r = rightChild_hs(index);
    if (r < heapSize && heap[r] > heap[maxIndex]) {
        maxIndex = r;
    }
    if (index != maxIndex) {
        std::swap(heap[index], heap[maxIndex]);
        siftDown_hs(heap, heapSize, maxIndex);
    }
}

void buildHeap_hs(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = (n / 2) - 1; i >= 0; i--) {
        siftDown_hs(arr, n, i);
    }
}

void heapSort_hs(std::vector<int>& arr) { // Zmieniamy nazwę funkcji głównej sortującej
    int n = arr.size();
    buildHeap_hs(arr);
    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        siftDown_hs(arr, i, 0);
    }
}


int main() { // Główny main łączący wszystko
    std::cout << "--- Przykład dodawania (Push) ---" << std::endl;
    main_push_example(); // Wywołujemy funkcję z przykładem push
    std::cout << std::endl;

    std::cout << "--- Przykład usuwania (Pop) ---" << std::endl;
    main_pop_example(); // Wywołujemy funkcję z przykładem pop
    std::cout << std::endl;

    std::cout << "--- Przykład budowania kopca (BuildHeap) ---" << std::endl;
    main_build_example(); // Wywołujemy funkcję z przykładem build
    std::cout << std::endl;
    
    std::cout << "--- Przykład Heapsort ---" << std::endl;
    std::vector<int> data_hs = {12, 11, 13, 5, 6, 7, 20, 1, 30};
    std::cout << "Tablica przed sortowaniem: ";
    printArray_heapsort(data_hs);

    heapSort_hs(data_hs); // Używamy funkcji sortującej z _hs

    std::cout << "Tablica po Heapsort:       ";
    printArray_heapsort(data_hs);
    std::cout << std::endl;

    return 0;
}
```
*Mała uwaga: W powyższym kodzie C++ dodałem `_hs` do niektórych nazw funkcji w sekcji Heapsort, aby uniknąć konfliktów nazw, jeśli chciałbyś skompilować wszystkie części razem. W finalnym `main` wywołuję przykładowe funkcje, ale pamiętaj, że każda z nich potrzebuje odpowiednich definicji funkcji pomocniczych (siftUp, siftDown, parent, leftChild, rightChild). Upewniłem się, że w ostatnim przykładzie (main) są wszystkie potrzebne funkcje.*

---



> Pomaga szybko znaleźć największy (lub najmniejszy) element i super nadaje się do sortowania. Mam nadzieję, że teraz już trochę bardziej kumasz, o co w tym wszystkim chodzi. Jakby co, pytaj śmiało! Powodzenia z klockami! 😉


