# Najkrótsze ścieżki

W folderze znajdują się przykładowe implementacje dwóch algorytmów:

* **Dijkstra** – klasyczny algorytm wyznaczający najkrótsze ścieżki w grafie o nieujemnych wagach. Przeszukuje graf bez dodatkowej wiedzy o położeniu celu.
* **A\*** – algorytm informowany, który oprócz dotychczasowego kosztu korzysta z heurystyki (tutaj: odległość euklidesowa w przestrzeni współrzędnych wierzchołków). Heurystyka prowadzi wyszukiwanie w stronę celu, co zwykle ogranicza liczbę odwiedzanych wierzchołków.

Główna różnica polega więc na wykorzystaniu heurystyki: A\* może działać szybciej, jeśli heurystyka jest dopuszczalna (nie przeszacowuje rzeczywistego kosztu), natomiast Dijkstra nie wymaga dodatkowych informacji o grafie.
