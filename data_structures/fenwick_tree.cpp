#include <cstddef>
#include <vector>

// Fenwick Tree (Binary Indexed Tree) for prefix sums and range queries
class FenwickTree {
  std::vector<long long> bit;  // binary indexed tree
  std::size_t n;

 public:
  explicit FenwickTree(std::size_t n) : bit(n + 1, 0), n(n) {}

  explicit FenwickTree(const std::vector<long long> &data)
      : FenwickTree(data.size()) {
    for (std::size_t i = 0; i < data.size(); ++i) {
      add(i, data[i]);
    }
  }

  // Adds `value` at position `index`
  void add(std::size_t index, long long value) {
    for (++index; index <= n; index += index & -index) {
      bit[index] += value;
    }
  }

  // Returns prefix sum on range [0, index]
  long long prefix_sum(std::size_t index) const {
    long long result = 0;
    for (++index; index > 0; index -= index & -index) {
      result += bit[index];
    }
    return result;
  }

  // Returns sum on range [left, right]
  long long range_sum(std::size_t left, std::size_t right) const {
    if (right < left) {
      return 0;
    }
    return prefix_sum(right) - (left == 0 ? 0 : prefix_sum(left - 1));
  }
};

