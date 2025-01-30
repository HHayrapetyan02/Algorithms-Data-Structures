#include <iostream>
#include <vector>

using Vertex = int32_t;
using AdjList = std::vector<std::vector<Vertex>>;
enum class Color { kWhite, kGray, kBlack };

class Graph {
  int32_t n_ = 0;
  int32_t m_ = 0;
  AdjList adj_;

 public:
  Graph() = default;
  Graph(const int32_t&, const int32_t&);
  bool HasCycle(std::vector<Vertex>&, int32_t&);
  bool RecursiveHasCycle(Vertex, std::vector<Color>&, std::vector<Vertex>&, int32_t&);
  friend std::istream& operator>>(std::istream&, Graph&);
};

Graph::Graph(const int32_t& n, const int32_t& m) : n_(n), m_(m), adj_(n + 1) {
}

bool Graph::RecursiveHasCycle(Vertex vertex, std::vector<Color>& color, std::vector<Vertex>& parent, int32_t& last) {
  color[vertex] = Color::kGray;
  for (const auto& edge : adj_[vertex]) {
    if (color[edge] == Color::kGray || (color[edge] == Color::kWhite && RecursiveHasCycle(edge, color, parent, last))) {
      parent.emplace_back(vertex);
      if (last == 0) {
        last = edge;
      }
      return true;
    }
  }
  color[vertex] = Color::kBlack;
  return false;
}

bool Graph::HasCycle(std::vector<Vertex>& parent, int32_t& last) {
  std::vector<Color> color(n_ + 1, Color::kWhite);
  for (Vertex vertex = 1; vertex < n_ + 1; ++vertex) {
    if (color[vertex] == Color::kWhite && RecursiveHasCycle(vertex, color, parent, last)) {
      return true;
    }
    parent.clear();
  }
  return false;
}

std::istream& operator>>(std::istream& io, Graph& graph) {
  io >> graph.n_ >> graph.m_;
  graph.adj_.resize(graph.n_ + 1);
  for (int32_t i = 0; i < graph.m_; ++i) {
    Vertex begin = 0;
    Vertex end = 0;
    io >> begin >> end;
    graph.adj_[begin].emplace_back(end);
  }
  return io;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  Graph graph;
  std::cin >> graph;
  std::vector<Vertex> parent;
  int32_t last = 0;
  if (graph.HasCycle(parent, last)) {
    std::cout << "YES\n";
    size_t size = parent.size() - 1;
    while (parent[size] != last) {
      --size;
    }
    for (auto i = static_cast<int32_t>(size); i >= 0; --i) {
      std::cout << parent[i] << " ";
    }
  } else {
    std::cout << "NO\n";
  }
  return 0;
}
