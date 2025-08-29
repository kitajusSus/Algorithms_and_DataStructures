# Segment Tree

Segment Tree to struktura danych umożliwiająca obsługę zapytań na przedziałach
oraz aktualizacji punktowych w czasie O(log n).

## Przykład użycia

```cpp
#include "segment_tree.cpp"
#include <iostream>
#include <vector>

int main() {
  std::vector<long long> data = {1, 2, 3, 4, 5};
  SegmentTree st(data);

  std::cout << st.query(1, 3) << "\n"; // suma na [1,3] = 9
  st.update(2, 10);                    // ustaw a[2] = 10
  std::cout << st.query(1, 3) << "\n"; // nowa suma na [1,3] = 16
}
```

Prefix sum można uzyskać wywołując `query(0, index)`.

