# nowe metody sortowania

## **Opis programów**

### zadanie1.cpp
[Zadanie1.cpp](zadanie1.cpp)

Sortowanie Bombelkowe generalnie zrobiłem już w [Link](../zaj2/bubble_sort.cpp) Ale tutaj zrobie sortowanie te drugie. i wytłumaczę, 

1. **Zasada działania**:
- Dzielimy tablicę na dwie części: posortowaną (początkowo pierwszy element) i nieposortowaną.
- Iterujemy przez nieposortowaną część, biorąc jeden element na raz.
- Dla każdego elementu (klucza) z nieposortowanej części, znajdujemy jego właściwą pozycję w posortowanej części i wstawiamy go tam.

2. **Proces krok po kroku**:
- Zaczynamy od indeksu 1 (drugi element), zakładając że pierwszy element (indeks 0) jest już posortowany.
- Pobieramy element do zmiennej key.
- Porównujemy key z elementami w posortowanej części tablicy (elementy przed key).
- Przesuwamy wszystkie elementy większe od key o jedną pozycję w prawo.
Wstawiamy key na właściwą pozycję.

Dodatkowo zrobiłem kodzik który robi to samo ale mniej klas czyli [zadanie1a.cpp bez using namespace wiec nie bójcie sie ](zadanie1a.cpp) 

**Omówienie zadanie1.cpp**
Tak o zaczynamy od klasycznych rzeczy typu. Zrobienie classy