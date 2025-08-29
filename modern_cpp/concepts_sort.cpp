#include <algorithm>
#include <concepts>
#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <ranges>

// Koncept ograniczający zakres do kontenerów z losowym dostępem
// i elementów, które można porównać oraz posortować
template <typename R>
concept SortableRange =
  std::ranges::random_access_range<R> &&
  std::sortable<std::ranges::iterator_t<R>>;

template <SortableRange R>
void sort_and_print(R& r) {
  std::ranges::sort(r);
  for (const auto& elem : r) {
    std::cout << elem << ' ';
  }
  std::cout << '\n';
}

int main() {
  std::vector<int> data{5, 1, 4, 2, 3};
  sort_and_print(data);

  std::array<std::string, 3> words{"ala", "kota", "ma"};
  sort_and_print(words);

  // std::list<int> lst{3, 1, 2};
  // sort_and_print(lst); // Błąd kompilacji: lista nie spełnia SortableRange

  return 0;
}
