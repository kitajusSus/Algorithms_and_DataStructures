# Najdłuższy wspólny podciąg (LCS)

## Tablica DP
1. Tworzymy tablicę `dp[i][j]`, która przechowuje długość LCS dla prefiksów `a[0..i-1]` i `b[0..j-1]`.
2. Pierwszy wiersz i kolumna są zerami – pusty napis ma LCS długości `0` z dowolnym innym napisem.
3. Dla każdej pary indeksów `(i, j)`:
   - Jeśli `a[i-1] == b[j-1]`, ustawiamy `dp[i][j] = dp[i-1][j-1] + 1`.
   - W przeciwnym razie `dp[i][j] = max(dp[i-1][j], dp[i][j-1])`.
4. Wartość w `dp[n][m]` to długość najdłuższego wspólnego podciągu całych napisów.

## Rekonstrukcja rozwiązania
1. Startujemy z pozycji `(n, m)` i cofamy się po tablicy.
2. Jeśli `a[i-1] == b[j-1]`, znak ten należy do LCS – dodajemy go i przechodzimy do `(i-1, j-1)`.
3. W przeciwnym razie porównujemy `dp[i-1][j]` i `dp[i][j-1]`:
   - Gdy `dp[i-1][j] >= dp[i][j-1]`, zmniejszamy `i`.
   - W przeciwnym przypadku zmniejszamy `j`.
4. Po dojściu do pierwszego wiersza lub kolumny odwracamy zebrane znaki – otrzymujemy szukany podciąg.
