#include <iostream>

void Solution(int** arr, int x, int y, int max_x, int max_y) {
  int now_x = 1;
  int now_y = 1;
  int coord_x = 0;
  int coord_y = 0;

  int max = arr[coord_x][coord_y];
  while (true) {
    if (now_x == coord_x && now_y == coord_y) {
      break;
    }
    now_x = coord_x;
    now_y = coord_y;
    for (int i = now_x; i < std::min(x, now_x + max_x); ++i) {
      for (int j = now_y; j < std::min(y, now_y + max_y); ++j) {
        if (max < arr[i][j]) {
          max = arr[i][j];
          coord_x = i;
          coord_y = j;
        }
      }
    }
  }
  std::cout << coord_x << " " << coord_y << "\n";
}

int main() {
  int x = 0;
  int y = 0;
  std::cin >> x >> y;
  int max_x = 0;
  int max_y = 0;
  std::cin >> max_x >> max_y;

  auto arr = new int*[x];
  for (int i = 0; i < x; ++i) {
    arr[i] = new int[y]{};
  }
  for (int i = 0; i < x; ++i) {
    for (int j = 0; j < y; ++j) {
      std::cin >> arr[i][j];
    }
  }
  Solution(arr, x, y, max_x, max_y);
  for (int i = 0; i < x; ++i) {
    delete[] arr[i];
  }
  delete[] arr;
  return 0;
}
