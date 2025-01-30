#include <iostream>
#include <vector>

using Vertex = int32_t;
using AdjList = std::vector<std::vector<Vertex>>;
enum class Color { kWhite, kGray, kBlack };

class Graph {
  int32_t n_ = 0;
  AdjList adj_;

 public:
  Graph() = default;
  explicit Graph(int32_t);
  int64_t HasCycle() const;
  bool RecursiveHasCycle(Vertex, std::vector<Color>&) const;
  friend std::istream& operator>>(std::istream&, Graph&);
};

Graph::Graph(int32_t n) : n_(n), adj_(n + 1) {
}

int64_t Graph::HasCycle() const {
  int64_t count = 0;
  std::vector<Color> color(n_ + 1, Color::kWhite);

  for (Vertex vertex = 1; vertex < n_ + 1; ++vertex) {
    if (color[vertex] == Color::kWhite && RecursiveHasCycle(vertex, color)) {
      ++count;
    }
  }
  return count;
}

bool Graph::RecursiveHasCycle(Vertex vertex, std::vector<Color>& color) const {
  bool flag = false;
  color[vertex] = Color::kGray;

  for (const auto& edge : adj_[vertex]) {
    if (color[edge] == Color::kGray || (color[edge] == Color::kWhite && RecursiveHasCycle(edge, color))) {
      flag = true;
    }
  }
  color[vertex] = Color::kBlack;
  return flag;
}

std::istream& operator>>(std::istream& io, Graph& graph) {
  io >> graph.n_;
  graph.adj_.resize(graph.n_ + 1);
  for (int32_t i = 1; i < graph.n_ + 1; ++i) {
    Vertex vertex = 0;
    io >> vertex;
    graph.adj_[i].emplace_back(vertex);
  }
  return io;
}

int main() {
  Graph graph;
  std::cin >> graph;
  std::cout << graph.HasCycle() << "\n";
  return 0;
}
