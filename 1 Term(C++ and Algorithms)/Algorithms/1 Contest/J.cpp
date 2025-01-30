#include <iostream>
using std::string;

void Reverse(char* arr, int size) {
  for (int i = 0; i < size / 2; ++i) {
    char temp = arr[i];
    arr[i] = arr[size - 1 - i];
    arr[size - 1 - i] = temp;
  }
}
int main() {
  std::string str;
  std::cin >> str;
  int len = str.size() - 1;
  auto arr_1 = new char[(len + 1) / 2];
  auto arr_2 = new char[len - (len + 1) / 2];
  for (int i = 0; i < len; i += 2) {
    arr_1[i / 2] = str[i];
  }
  for (int i = 1; i < len; i += 2) {
    arr_2[(i - 1) / 2] = str[i];
  }
  Reverse(arr_2, len - (len + 1) / 2);
  for (int i = 0; i < (len + 1) / 2; ++i) {
    std::cout << arr_1[i];
  }
  for (int i = 0; i < len - (len + 1) / 2; ++i) {
    std::cout << arr_2[i];
  }
  delete[] arr_1;
  delete[] arr_2;
  std::cin.get();
  return 0;
}
