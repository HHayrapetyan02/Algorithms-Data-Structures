#include <iostream>
#include <vector>

using Vertex = int32_t;
enum class Color { kWhite, kGray, kBlack };
using Table = std::vector<std::vector<int32_t>>;

class Graph {
  int32_t n_ = 0;
  int32_t m_ = 0;
  std::vector<std::vector<Vertex>> adj_;

 public:
  Graph() = default;
  explicit Graph(int32_t, int32_t);
  int64_t DFS(std::vector<int32_t>&, Table&) const;
  void RecursiveDfsVisit(Vertex, int&, std::vector<Color>&, std::vector<int32_t>&) const;
  friend std::istream& operator>>(std::istream&, Graph&);
};

Graph::Graph(int32_t n, int32_t m) : n_(n), m_(m), adj_(n + 1) {
}

int64_t Graph::DFS(std::vector<int32_t>& number, Table& table) const {
  int64_t count = 0;
  std::vector<Color> color(n_ + 1, Color::kWhite);
  for (Vertex vertex = 1; vertex < n_ + 1; ++vertex) {
    if (color[vertex] == Color::kWhite) {
      std::vector<int> arr(1, vertex);
      table.emplace_back(arr);
      int32_t curr_time = 0;
      RecursiveDfsVisit(vertex, curr_time, color, table[table.size() - 1]);
      number.emplace_back(curr_time);
      ++count;
    }
  }
  return count;
}

void Graph::RecursiveDfsVisit(Vertex vertex, int32_t& curr_time, std::vector<Color>& color,
                              std::vector<int32_t>& table) const {
  color[vertex] = Color::kGray;
  ++curr_time;

  for (auto edge : adj_[vertex]) {
    if (color[edge] == Color::kWhite) {
      table.emplace_back(edge);
      RecursiveDfsVisit(edge, curr_time, color, table);
    }
  }
  color[vertex] = Color::kBlack;
}

std::istream& operator>>(std::istream& io, Graph& graph) {
  io >> graph.n_ >> graph.m_;
  graph.adj_.resize(graph.n_ + 1);
  for (int32_t i = 0; i < graph.m_; ++i) {
    Vertex begin = 0;
    Vertex end = 0;
    io >> begin >> end;
    graph.adj_[begin].emplace_back(end);
    graph.adj_[end].emplace_back(begin);
  }
  return io;
}

int main() {
  Graph graph;
  std::cin >> graph;
  std::vector<int32_t> number;
  Table table;
  int64_t count = graph.DFS(number, table);
  std::cout << count << "\n";
  for (auto i = 0; i < count; ++i) {
    std::cout << number[i] << "\n";
    for (const auto v : table[i]) {
      std::cout << v << " ";
    }
    std::cout << "\n";
  }
  return 0;
}
