#include <iostream>

int Solution(int n, int* arr, int* ans) {
  int count = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < arr[i]; ++j) {
      ans[arr[i]] += ans[j];
    }
    ans[arr[i]] += 1;
    ans[arr[i]] %= 1000000;
  }

  for (int i = 0; i < 5010; ++i) {
    count += ans[i];
  }

  return count;
}

int main() {
  int n = 0;
  std::cin >> n;
  const int len = 5010;

  auto arr = new int[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }
  auto ans = new int[len]{0};

  int answer = Solution(n, arr, ans);
  std::cout << answer % 1000000 << "\n";

  delete[] arr;
  delete[] ans;
  return 0;
}
