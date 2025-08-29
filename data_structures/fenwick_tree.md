# Fenwick Tree

Fenwick Tree (drzewo Fenwicka) umożliwia szybkie obliczanie sum prefiksowych
oraz zapytań na przedziałach w czasie O(log n).

## Przykład użycia

```cpp
#include "fenwick_tree.cpp"
#include <iostream>
#include <vector>

int main() {
  std::vector<long long> data = {1, 2, 3, 4, 5};
  FenwickTree ft(data); // zbuduj na podstawie danych

  std::cout << ft.prefix_sum(3) << "\n";       // suma [0..3] = 10
  std::cout << ft.range_sum(1, 3) << "\n";     // suma [1..3] = 9

  ft.add(2, 6); // zwiększ element na pozycji 2 o 6
  std::cout << ft.range_sum(1, 3) << "\n";     // nowy wynik: 15
}
```

