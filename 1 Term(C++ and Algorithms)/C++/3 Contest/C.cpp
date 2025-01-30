#include <iostream>
#include <algorithm>

struct Problem {
  int num = 0;
  int count = 0;
  int time = 0;
};

bool Greater(const Problem& a, const Problem& b) {
  if (a.count < b.count) {
    return false;
  }
  if (a.count > b.count) {
    return true;
  }
  if (a.time > b.time) {
    return false;
  }
  if (a.time < b.time) {
    return true;
  }
  if (a.num > b.num) {
    return false;
  }
  return true;
}

int main() {
  int n = 0;
  std::cin >> n;
  auto a = new Problem[n]{};
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i].count >> a[i].time;
    a[i].num = i + 1;
  }
  std::stable_sort(a, a + n, Greater);
  for (int i = 0; i < n; ++i) {
    std::cout << a[i].num << "\n";
  }
  delete[] a;
  return 0;
}
