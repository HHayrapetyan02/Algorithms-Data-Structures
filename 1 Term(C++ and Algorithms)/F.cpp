#include <iostream>

void Merge(int* arr, int left, int right, int mid, int64_t& ans) {
  auto a = new int[right - left + 1];
  int i = 0;
  int first = left;
  int second = mid + 1;
  while (first <= mid && second <= right) {
    if (arr[first] <= arr[second]) {
      a[i] = arr[first];
      ++first;
      ++i;
    } else {
      a[i] = arr[second];
      ans += mid - first + 1;
      ++second;
      ++i;
    }
  }
  while (first <= mid) {
    a[i] = arr[first];
    ++first;
    ++i;
  }
  while (second <= right) {
    a[i] = arr[second];
    ++second;
    ++i;
  }
  for (int i = 0; i < right - left + 1; ++i) {
    arr[left + i] = a[i];
  }
  delete[] a;
}

void MergeSort(int* arr, int left, int right, int64_t& ans) {
  if (left >= right) {
    return;
  }
  int mid = (right - left) / 2 + left;
  MergeSort(arr, left, mid, ans);
  MergeSort(arr, mid + 1, right, ans);
  Merge(arr, left, right, mid, ans);
}

int main() {
  int n = 0;
  int64_t ans = 0;
  std::cin >> n;
  auto arr = new int[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }
  MergeSort(arr, 0, n - 1, ans);
  std::cout << ans;
  delete[] arr;
  return 0;
}
