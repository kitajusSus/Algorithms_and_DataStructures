#include <iostream>
#include <vector>

using namespace std;

long long operationCount = 0;

void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1);
    vector<int> R(n2);

    for (int i = 0; i < n1; ++i) {
        L[i] = arr[left + i];
        operationCount++; // assignment
    }
    for (int j = 0; j < n2; ++j) {
        R[j] = arr[mid + 1 + j];
        operationCount++; // assignment
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        operationCount++; // comparison
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
            operationCount++; // assignment
        } else {
            arr[k++] = R[j++];
            operationCount++; // assignment
        }
    }

    while (i < n1) {
        arr[k++] = L[i++];
        operationCount++; // assignment
    }
    while (j < n2) {
        arr[k++] = R[j++];
        operationCount++; // assignment
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right)
        return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

int main() {
    vector<int> data = {38, 27, 43, 3, 9, 82, 10};

    mergeSort(data, 0, data.size() - 1);

    cout << "Posortowana tablica: ";
    for (int x : data)
        cout << x << ' ';
    cout << "\nLiczba operacji: " << operationCount << endl;

    return 0;
}

