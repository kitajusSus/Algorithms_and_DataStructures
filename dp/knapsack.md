# Problem plecakowy 0/1

## Tablica DP
1. Definiujemy `dp[i][j]` jako maksymalną wartość, jaką można uzyskać z pierwszych `i` przedmiotów, mając do dyspozycji pojemność `j`.
2. Inicjalizujemy pierwszy wiersz i pierwszą kolumnę zerami – dla `0` przedmiotów lub pojemności `0` wartość jest równa `0`.
3. Dla każdego przedmiotu `i` oraz każdej pojemności `j` wykonujemy:
   - Jeśli `waga[i] > j`, przepisujemy wynik z wiersza wyżej: `dp[i][j] = dp[i-1][j]`.
   - W przeciwnym razie wybieramy lepszą z dwóch opcji: nie bierzemy przedmiotu (`dp[i-1][j]`) lub bierzemy go (`dp[i-1][j-waga[i]] + wartosc[i]`).
4. Odpowiedź `dp[n][W]` zawiera maksymalną wartość dla wszystkich przedmiotów i pełnej pojemności plecaka.

## Rekonstrukcja rozwiązania
1. Zaczynamy od komórki `dp[n][W]` i cofamy się w górę tabeli.
2. Jeśli `dp[i][j] == dp[i-1][j]`, przedmiot `i` nie został użyty – zmniejszamy `i`.
3. W przeciwnym razie przedmiot `i` znajduje się w optymalnym rozwiązaniu – zapisujemy go i zmniejszamy `j` o `waga[i]`, a następnie zmniejszamy `i`.
4. Po dojściu do `i = 0` odczytane przedmioty (w odwrotnej kolejności) tworzą optymalny zestaw.
