#include <iostream>
#include <vector>
#include <deque>

using Vertex = int32_t;
enum class Color { kWhite, kGray, kBlack };

class Graph {
 public:
  int32_t n = 0;
  int32_t m = 0;
  std::vector<std::vector<Vertex>> adj;

  Graph() = default;
  explicit Graph(const int32_t&, const int32_t&);
  bool TwoGroups();
  friend std::istream& operator>>(std::istream&, const Graph&);
};

Graph::Graph(const int32_t& n, const int32_t& m) : n(n), m(m), adj(n + 1) {
}

bool Graph::TwoGroups() {
  std::vector<Color> color(n + 1, Color::kWhite);
  for (int32_t i = 1; i < n + 1; ++i) {
    if (color[i] == Color::kWhite) {
      color[i] = Color::kBlack;
      std::deque<Vertex> queue{i};
      while (!queue.empty()) {
        auto curr = queue.front();
        queue.pop_front();
        for (auto edge : adj[curr]) {
          if (color[edge] == Color::kWhite) {
            if (color[curr] == Color::kBlack) {
              color[edge] = Color::kGray;
            } else {
              color[edge] = Color::kBlack;
            }
            queue.emplace_back(edge);
          } else if (color[curr] == color[edge]) {
            return false;
          }
        }
      }
    }
  }
  return true;
}

std::istream& operator>>(std::istream& io, Graph& graph) {
  io >> graph.n >> graph.m;
  graph.adj.resize(graph.n + 1);
  for (int32_t i = 0; i < graph.m; ++i) {
    Vertex begin = 0;
    Vertex finish = 0;
    io >> begin >> finish;
    graph.adj[begin].push_back(finish);
    graph.adj[finish].push_back(begin);
  }
  return io;
}

int main() {
  Graph graph;
  std::cin >> graph;
  if (graph.TwoGroups()) {
    std::cout << "YES"
              << "\n";
  } else {
    std::cout << "NO"
              << "\n";
  }
  return 0;
}
