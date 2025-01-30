#include <iostream>

int Max(int a, int b) {
  int max = b;
  if (b < a) {
    max = a;
  }
  return max;
}

void Swap(int& a, int& b) {
  int tmp = a;
  a = b;
  b = tmp;
}

void QuickSort(int* arr, int n) {
  int i = 0;
  int j = n - 1;
  int mid = arr[n / 2];
  while (i <= j) {
    while (arr[i] < mid) {
      i++;
    }
    while (arr[j] > mid) {
      j--;
    }
    if (i <= j) {
      Swap(arr[i], arr[j]);
      i++;
      j--;
    }
  }
  if (j > 0) {
    QuickSort(arr, j + 1);
  }
  if (i < n) {
    QuickSort(&arr[i], n - i);
  }
}
void Delete(int* a, int* b, int size) {
  int tmp = 1;
  b[0] = a[0];
  for (int i = 1; i < size; ++i) {
    if (a[i] != a[i - 1]) {
      b[tmp] = a[i];
      ++tmp;
    }
  }
}

int main() {
  int n = 0;
  int m = 0;
  int k = 0;
  bool flag = true;
  std::cin >> n;
  auto arr = new int[n]{};
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }

  std::cin >> m;
  auto b = new int[m]{};
  for (int i = 0; i < m; ++i) {
    std::cin >> b[i];
  }

  QuickSort(arr, n);
  QuickSort(b, m);

  k = Max(m, n);

  auto arr1 = new int[k]{};
  auto b1 = new int[k]{};
  Delete(arr, arr1, n);
  Delete(b, b1, m);
  for (int i = 0; i < k; ++i) {
    if (arr1[i] != b1[i]) {
      flag = false;
    }
  }
  if (flag) {
    std::cout << "YES"
              << "\n";
  } else {
    std::cout << "NO"
              << "\n";
  }
  delete[] arr;
  delete[] b;
  delete[] arr1;
  delete[] b1;
  return 0;
}
