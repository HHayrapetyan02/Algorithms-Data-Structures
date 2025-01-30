#include <iostream>
#include <vector>

using Vertex = int;

class Graph {
 public:
  int n = 0;
  std::vector<std::vector<Vertex>> adj;

  Graph() = default;
  explicit Graph(const int&);
};

Graph::Graph(const int& n) : n(n), adj(n + 1) {
}

int main() {
  int n = 0;
  std::cin >> n;
  Graph graph(n);
  int k = 0;
  std::cin >> k;
  for (int i = 0; i < k; ++i) {
    int command = 0;
    std::cin >> command;
    if (command == 1) {
      Vertex u = 0;
      Vertex v = 0;
      std::cin >> u >> v;
      graph.adj[u].emplace_back(v);
      graph.adj[v].emplace_back(u);
    } else {
      Vertex u = 0;
      std::cin >> u;
      for (const auto& edge : graph.adj[u]) {
        std::cout << edge << " ";
      }
      std::cout << "\n";
    }
  }
  return 0;
}
