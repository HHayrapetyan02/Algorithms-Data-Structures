#include <iostream>
#include <algorithm>

struct Students {
  char surname[40];
  char name[40];
  int inf;
  int math;
  int rus;
  int sum;
};

bool Greater(Students a, Students b) {
  return !(a.sum <= b.sum);
}

int main() {
  int n = 0;
  std::cin >> n;
  auto arr = new Students[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i].surname >> arr[i].name >> arr[i].inf >> arr[i].math >> arr[i].rus;
  }

  for (int i = 0; i < n; ++i) {
    arr[i].sum = arr[i].inf + arr[i].math + arr[i].rus;
  }

  std::stable_sort(arr, arr + n, Greater);

  for (int i = 0; i < n; ++i) {
    std::cout << arr[i].surname << " " << arr[i].name << "\n";
  }

  delete[] arr;
  return 0;
}
