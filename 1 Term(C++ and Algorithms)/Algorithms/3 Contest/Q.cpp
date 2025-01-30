#include <iostream>
#include <limits>

const int32_t kMaxN = 201;
const int32_t kInf = std::numeric_limits<int32_t>::max();

int32_t MinCntOper(int32_t** cnt_oper, int32_t* arr, int32_t left, int32_t right) {
  if (cnt_oper[left][right] == -1) {
    if (left - right == -1) {
      cnt_oper[left][right] = 0;
    } else {
      cnt_oper[left][right] = kInf;
      for (int32_t i = left + 1; i < right; ++i) {
        int32_t first_val = cnt_oper[left][right];
        int32_t second_val = arr[left] * arr[i] * arr[right];
        int32_t third_val = MinCntOper(cnt_oper, arr, left, i) + MinCntOper(cnt_oper, arr, i, right);
        cnt_oper[left][right] = std::min(first_val, second_val + third_val);
      }
    }
  }
  return cnt_oper[left][right];
}

int main() {
  int32_t n = 0;
  std::cin >> n;
  auto arr = new int32_t[n]{};
  for (int32_t i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }
  auto cnt_oper = new int32_t*[kMaxN];
  for (int32_t i = 0; i < 201; ++i) {
    cnt_oper[i] = new int32_t[kMaxN];
  }
  for (int32_t i = 0; i < kMaxN; ++i) {
    for (int32_t j = 0; j < kMaxN; ++j) {
      cnt_oper[i][j] = -1;
    }
  }
  std::cout << MinCntOper(cnt_oper, arr, 0, n - 1) << "\n";

  delete[] arr;
  for (int32_t i = 0; i < 201; ++i) {
    delete[] cnt_oper[i];
  }
  delete[] cnt_oper;
  return 0;
}
