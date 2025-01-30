#include <iostream>
#include <vector>

using Vertex = int32_t;
enum class Color { kWhite, kGray, kBlack };
using AdjList = std::vector<std::vector<Vertex>>;

class Graph {
  int32_t n_ = 0;
  AdjList adj_;

 public:
  Graph() = default;
  explicit Graph(int32_t);
  bool HasCycle() const;
  bool RecursiveHasCycle(Vertex, std::vector<Color>&) const;
  friend std::istream& operator>>(std::istream&, Graph&);
};

Graph::Graph(int32_t n) : n_(n), adj_(n + 1) {
}

bool Graph::RecursiveHasCycle(Vertex vertex, std::vector<Color>& color) const {
  color[vertex] = Color::kGray;
  for (auto edge : adj_[vertex]) {
    if (color[edge] == Color::kGray || (color[edge] == Color::kWhite && RecursiveHasCycle(edge, color))) {
      return true;
    }
  }
  color[vertex] = Color::kBlack;
  return false;
}

bool Graph::HasCycle() const {
  std::vector<Color> color(n_ + 1, Color::kWhite);
  for (Vertex vertex = 1; vertex < n_ + 1; ++vertex) {
    if (color[vertex] == Color::kWhite && RecursiveHasCycle(vertex, color)) {
      return true;
    }
  }
  return false;
}

std::istream& operator>>(std::istream& io, Graph& graph) {
  io >> graph.n_;
  graph.adj_.resize(graph.n_ + 1);
  for (int32_t i = 1; i < graph.n_; ++i) {
    for (int32_t j = i + 1; j <= graph.n_; ++j) {
      char str = ' ';
      std::cin >> str;
      if (str == 'R') {
        graph.adj_[j].emplace_back(i);
      } else {
        graph.adj_[i].emplace_back(j);
      }
    }
  }
  return io;
}

int32_t main() {
  std::ios_base::sync_with_stdio(false);
  Graph graph;
  std::cin >> graph;
  if (graph.HasCycle()) {
    std::cout << "NO"
              << "\n";
  } else {
    std::cout << "YES"
              << "\n";
  }
  return 0;
}
