#include <cstddef>
#include <vector>

// Segment Tree for range sum queries and point updates
class SegmentTree {
  std::size_t size;
  std::vector<long long> tree;

  void build(const std::vector<long long> &data, std::size_t node,
             std::size_t l, std::size_t r) {
    if (l == r) {
      tree[node] = data[l];
      return;
    }
    std::size_t mid = l + (r - l) / 2;
    build(data, node * 2, l, mid);
    build(data, node * 2 + 1, mid + 1, r);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
  }

  long long query(std::size_t node, std::size_t l, std::size_t r,
                  std::size_t ql, std::size_t qr) const {
    if (qr < l || r < ql) {
      return 0;
    }
    if (ql <= l && r <= qr) {
      return tree[node];
    }
    std::size_t mid = l + (r - l) / 2;
    return query(node * 2, l, mid, ql, qr) +
           query(node * 2 + 1, mid + 1, r, ql, qr);
  }

  void update(std::size_t node, std::size_t l, std::size_t r, std::size_t index,
              long long value) {
    if (l == r) {
      tree[node] = value;
      return;
    }
    std::size_t mid = l + (r - l) / 2;
    if (index <= mid) {
      update(node * 2, l, mid, index, value);
    } else {
      update(node * 2 + 1, mid + 1, r, index, value);
    }
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
  }

 public:
  explicit SegmentTree(const std::vector<long long> &data) {
    size = data.size();
    tree.assign(4 * size, 0);
    if (size > 0) {
      build(data, 1, 0, size - 1);
    }
  }

  // Returns sum on range [left, right]
  long long query(std::size_t left, std::size_t right) const {
    if (left > right || size == 0) {
      return 0;
    }
    return query(1, 0, size - 1, left, right);
  }

  // Updates position `index` with new `value`
  void update(std::size_t index, long long value) {
    if (index >= size) {
      return;
    }
    update(1, 0, size - 1, index, value);
  }
};

