#include <iostream>
#include <vector>

using Vertex = int32_t;
enum class Color { kWhite, kGray, kBlack };

class Graph {
  int32_t n_ = 0;
  int32_t m_ = 0;
  std::vector<std::vector<Vertex>> adj_;

 public:
  Graph() = default;
  explicit Graph(int32_t, int32_t);
  bool TopSort(std::vector<Vertex>&) const;
  bool RecursiveTopSort(Vertex, std::vector<Color>&, std::vector<Vertex>&) const;
  friend std::istream& operator>>(std::istream&, Graph&);
};

Graph::Graph(int32_t n, int32_t m) : n_(n), m_(m), adj_(n + 1) {
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

bool Graph::TopSort(std::vector<Vertex>& top_sorted) const {
  std::vector<Color> color(n_ + 1, Color::kWhite);
  for (Vertex vertex = 1; vertex < n_ + 1; ++vertex) {
    if (color[vertex] == Color::kWhite && !RecursiveTopSort(vertex, color, top_sorted)) {
      return false;
    }
  }
  return true;
}

bool Graph::RecursiveTopSort(Vertex vertex, std::vector<Color>& color, std::vector<Vertex>& top_sorted) const {
  color[vertex] = Color::kGray;
  for (auto edge : adj_[vertex]) {
    if (color[edge] == Color::kGray || (color[edge] == Color::kWhite && !RecursiveTopSort(edge, color, top_sorted))) {
      return false;
    }
  }
  color[vertex] = Color::kBlack;
  top_sorted.emplace_back(vertex);
  return true;
}

int main() {
  Graph graph;
  std::cin >> graph;
  std::vector<Vertex> top_sorted;
  if (graph.TopSort(top_sorted)) {
    for (auto i = static_cast<int32_t>(top_sorted.size() - 1); i >= 0; --i) {
      std::cout << top_sorted[i] << " ";
    }
  } else {
    std::cout << -1 << "\n";
  }
  return 0;
}
