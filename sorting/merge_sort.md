# Merge sort

Merge sort (sortowanie przez scalanie) dzieli tablicę na dwie połowy, rekurencyjnie sortuje każdą z nich, a następnie scala posortowane części w jedną tablicę. W implementacji wykorzystano licznik operacji, który zlicza porównania i przypisania wykonywane podczas scalania.

## Złożoność czasowa
W każdym kroku tablica dzielona jest na dwie części, a następnie scalana. Skutkuje to złożonością czasową `O(n log n)` w najlepszym, średnim i najgorszym przypadku.

## Złożoność pamięciowa
Algorytm wymaga dodatkowej tablicy pomocniczej do scalania, przez co jego złożoność pamięciowa wynosi `O(n)`.
