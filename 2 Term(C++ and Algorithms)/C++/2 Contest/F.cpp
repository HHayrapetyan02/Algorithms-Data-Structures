#include <iostream>
#include <string>
#include <unordered_map>

int main() {
  int n = 0;
  std::cin >> n;
  std::unordered_map<std::string, int> bank(n);
  for (int i = 0; i < n; ++i) {
    int command = 0;
    std::string name = " ";
    std::cin >> command >> name;
    if (command == 1) {
      int money = 0;
      std::cin >> money;
      if (bank.count(name) == 0) {
        bank[name] = money;
      } else {
        bank[name] += money;
      }
    } else {
      if (bank.count(name) == 0) {
        std::cout << "ERROR"
                  << "\n";
      } else {
        std::cout << bank[name] << "\n";
      }
    }
  }
  return 0;
}
