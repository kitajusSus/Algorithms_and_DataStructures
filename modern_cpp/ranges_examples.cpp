#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

int main() {
  std::vector<int> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  // Filtrowanie liczb parzystych i podnoszenie ich do kwadratu
  auto even_squares = numbers | std::views::filter([](int n) { return n % 2 == 0; }) |
                      std::views::transform([](int n) { return n * n; });

  std::cout << "Parzyste kwadraty:";
  for (int n : even_squares) {
    std::cout << ' ' << n;
  }
  std::cout << '\n';

  // Użycie algorytmu ranges
  bool all_even = std::ranges::all_of(even_squares, [](int n) { return n % 2 == 0; });
  std::cout << "Wszystkie elementy są parzyste? " << std::boolalpha << all_even << '\n';

  return 0;
}
