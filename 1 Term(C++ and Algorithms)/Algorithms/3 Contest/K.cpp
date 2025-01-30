#include <iostream>

void Solution(int n, int max_weight, int* weight, int* price) {
  auto max_price = new int32_t*[n + 1];
  for (int i = 0; i < n + 1; ++i) {
    max_price[i] = new int32_t[max_weight + 1]{};
  }
  for (int i = 0; i < n + 1; ++i) {
    for (int j = 0; j < max_weight + 1; ++j) {
      max_price[i][j] = 0;
    }
  }
  for (int i = 1; i < n + 1; ++i) {
    for (int j = 1; j < max_weight + 1; ++j) {
      if (weight[i] <= j) {
        max_price[i][j] = std::max(max_price[i - 1][j], max_price[i - 1][j - weight[i]] + price[i]);
      } else {
        max_price[i][j] = max_price[i - 1][j];
      }
    }
  }
  auto res = new int[n + 1]{};
  int len = 0;
  for (int i = n; i > 0; --i) {
    if (max_price[i][max_weight] != max_price[i - 1][max_weight]) {
      res[len] = i;
      max_weight -= weight[i];
      ++len;
    }
  }
  for (int i = len - 1; i >= 0; --i) {
    std::cout << res[i] << "\n";
  }
  for (int i = 0; i < n + 1; ++i) {
    delete[] max_price[i];
  }
  delete[] max_price;
  delete[] res;
}

int main() {
  int n = 0;
  int max_weight = 0;
  std::cin >> n >> max_weight;
  auto weight = new int[n + 1]{};
  auto price = new int[n + 1]{};

  for (int i = 1; i < n + 1; ++i) {
    std::cin >> weight[i];
  }
  for (int i = 1; i < n + 1; ++i) {
    std::cin >> price[i];
  }

  Solution(n, max_weight, weight, price);

  delete[] weight;
  delete[] price;
  return 0;
}
