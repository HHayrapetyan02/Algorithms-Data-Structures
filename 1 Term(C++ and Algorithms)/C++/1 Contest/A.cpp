#include <iostream>

void Config(char** arr, int& n, int& m) {
  int tmp_v = 0;
  int tmp_h = 0;
  int vert[2]{-1, -1};
  int hor[2]{-1, -1};
  for (int i = 0; i < n; ++i) {
    bool flag = true;
    for (int j = 0; j < m; ++j) {
      if (arr[i][j] == '0') {
        flag = false;
        break;
      }
    }
    if (flag) {
      ++tmp_h;
      if (hor[0] == -1) {
        hor[0] = i;
      } else if (hor[1] == -1) {
        hor[1] = i;
      }
    }
  }
  for (int i = 0; i < m; ++i) {
    bool flag = true;
    for (int j = 0; j < n; ++j) {
      if (arr[j][i] == '0') {
        flag = false;
        break;
      }
    }
    if (flag) {
      ++tmp_v;
      if (vert[0] == -1) {
        vert[0] = i;
      } else if (vert[1] == -1) {
        vert[1] = i;
      }
    }
  }
  if (n == 1) {
    tmp_v = 0;
  }
  if (m == 1) {
    tmp_h = 0;
  }
  int vertical = vert[1] - vert[0] - 1;
  int horizontal = hor[1] - hor[0] - 1;
  if ((tmp_h == 0 && tmp_v == 0) || (tmp_h == 1 && tmp_v == 0) || (tmp_h == 0 && tmp_v == 1)) {
    std::cout << "?";
  } else if (tmp_h >= 1 && tmp_v >= 1) {
    std::cout << "Square";
  } else if (tmp_h >= 2 && tmp_v == 0) {
    if (horizontal < m) {
      std::cout << "Line";
    } else {
      std::cout << "?";
    }
  } else if (tmp_h == 0 && tmp_v >= 2) {
    if (vertical < n) {
      std::cout << "Vertical line";
    } else {
      std::cout << "?";
    }
  }
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  auto arr = new char*[n];
  for (int i = 0; i < n; ++i) {
    arr[i] = new char[m];
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::cin >> arr[i][j];
    }
  }
  Config(arr, n, m);
  for (int i = 0; i < n; ++i) {
    delete[] arr[i];
  }
  delete[] arr;
}
