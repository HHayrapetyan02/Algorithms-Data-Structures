#include <iostream>
#include <vector>

using Weight = int32_t;
using EdgeList = std::vector<std::vector<int32_t>>;

class Graph {
  int32_t n_ = 0;
  EdgeList edges_;

 public:
  Graph() = default;
  explicit Graph(int32_t);
  void FloydWarshall();
  friend std::istream& operator>>(std::istream&, Graph&);
  friend std::ostream& operator<<(std::ostream&, const EdgeList&);
  void PrintEdges();
};

Graph::Graph(int32_t n) : n_(n) {
  edges_.resize(n, std::vector<int32_t>(n));
}

void Graph::FloydWarshall() {
  for (int32_t i = 0; i < n_; ++i) {
    for (int32_t j = 0; j < n_; ++j) {
      for (int32_t k = 0; k < n_; ++k) {
        int32_t min = std::min(edges_[j][k], edges_[j][i] + edges_[i][k]);
        edges_[j][k] = min;
      }
    }
  }
}

std::istream& operator>>(std::istream& io, Graph& graph) {
  for (int32_t i = 0; i < graph.n_; ++i) {
    for (int32_t j = 0; j < graph.n_; ++j) {
      Weight weight = 0;
      io >> weight;
      graph.edges_[i][j] = weight;
    }
  }
  return io;
}

std::ostream& operator<<(std::ostream& os, const EdgeList& edges) {
  for (const auto& string : edges) {
    for (const auto& elem : string) {
      os << elem << " ";
    }
    os << "\n";
  }
  return os;
}

void Graph::PrintEdges() {
  std::cout << edges_ << "\n";
}

int main() {
  int32_t n = 0;
  std::cin >> n;
  Graph graph(n);
  std::cin >> graph;
  graph.FloydWarshall();
  graph.PrintEdges();
  return 0;
}
