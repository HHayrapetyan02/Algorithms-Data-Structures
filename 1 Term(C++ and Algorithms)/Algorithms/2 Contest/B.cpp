#include <iostream>

void Swap(int64_t& x, int64_t& y) {
  int64_t tmp = x;
  x = y;
  y = tmp;
}

int64_t LeftChild(const int64_t& i) {
  return 2 * i + 1;
}

int64_t RightChild(const int64_t& i) {
  return 2 * i + 2;
}

int64_t PushHeap(int64_t* a, int64_t size) {
  int64_t index = size;
  while (a[index] > a[(index - 1) / 2]) {
    Swap(a[index], a[(index - 1) / 2]);
    index = (index - 1) / 2;
  }
  return index;
}

int64_t PopHeap(int64_t* a, int64_t n) {
  Swap(a[0], a[n - 1]);
  int64_t i = 0;
  int64_t left = 0;
  int64_t right = 0;
  int64_t res = 0;
  while (2 * i + 1 < n - 1) {
    left = LeftChild(i);
    right = RightChild(i);
    res = left;
    if ((right < n - 1) && a[right] > a[left]) {
      res = right;
    }
    if (a[i] >= a[res]) {
      return i;
    }
    Swap(a[i], a[res]);
    i = res;
  }
  return i;
}

int64_t Pop(int64_t* a, int64_t k, int64_t n) {
  int64_t tmp = a[k];
  a[k] = a[n - 1];
  a[n - 1] = tmp;
  int64_t i = k;
  int64_t left = 0;
  int64_t right = 0;
  int64_t res = 0;
  while (2 * i + 1 < n - 1) {
    left = LeftChild(i);
    right = RightChild(i);
    res = left;
    if ((right < n - 1) && (a[right] > a[left])) {
      res = right;
    }
    if (a[i] >= a[res]) {
      break;
    }
    Swap(a[i], a[res]);
    i = res;
  }
  i = k;
  while (*(a + i) > *(a + (i - 1) / 2)) {
    Swap(a[(i - 1) / 2], a[i]);
    i = (i - 1) / 2;
  }
  return tmp;
}

void PrintArray(int64_t* a, int64_t n) {
  for (int64_t i = 0; i < n; ++i) {
    std::cout << a[i] << " ";
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t n = 0;
  int64_t m = 0;
  int64_t size = 0;
  int64_t command = 0;
  std::cin >> n >> m;
  auto* arr = new int64_t[n + 1]{};
  for (int64_t i = 0; i < m; ++i) {
    std::cin >> command;
    if (command == 1) {
      if (size < 1) {
        std::cout << -1 << '\n';
      } else if (size == 1) {
        std::cout << 0 << " " << arr[0] << '\n';
        --size;
      } else {
        int64_t first = arr[0];
        std::cout << PopHeap(arr, size) + 1 << " " << first << '\n';
        --size;
      }
    }
    if (command == 2) {
      if (size == n) {
        int64_t y = 0;
        std::cin >> y;
        std::cout << -1 << '\n';
      } else {
        std::cin >> arr[size];
        std::cout << PushHeap(arr, size) + 1 << '\n';
        ++size;
      }
    }
    if (command == 3) {
      int64_t k = 0;
      std::cin >> k;
      if (k - 1 >= size || size == 0 || k < 1) {
        std::cout << -1 << '\n';
      } else {
        std::cout << Pop(arr, k - 1, size) << '\n';
        --size;
      }
    }
  }
  PrintArray(arr, size);
  delete[] arr;
  return 0;
}
