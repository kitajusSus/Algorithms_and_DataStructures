#include <vector>
#include <functional>
#include <algorithm>
#include <cassert>

void mergeSort(std::vector<int>& arr) {
    if (arr.size() <= 1) return;
    std::vector<int> tmp(arr.size());
    std::function<void(int,int)> rec = [&](int l, int r) {
        if (l >= r) return;
        int m = (l + r) / 2;
        rec(l, m);
        rec(m + 1, r);
        int i = l, j = m + 1, k = l;
        while (i <= m && j <= r) {
            if (arr[i] < arr[j]) tmp[k++] = arr[i++];
            else tmp[k++] = arr[j++];
        }
        while (i <= m) tmp[k++] = arr[i++];
        while (j <= r) tmp[k++] = arr[j++];
        for (int t = l; t <= r; ++t) arr[t] = tmp[t];
    };
    rec(0, arr.size() - 1);
}

int main() {
    std::vector<int> data = {5, 2, 9, 1, 5, 6};
    mergeSort(data);
    assert(std::is_sorted(data.begin(), data.end()));
    return 0;
}
