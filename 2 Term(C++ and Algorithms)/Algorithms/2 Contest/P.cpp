#include <iostream>
#include <vector>
#include <algorithm>

using Vertex = int32_t;
using Edge = std::pair<Vertex, Vertex>;
enum class Color { kWhite, kGray, kBlack };

class Graph {
  int32_t n_ = 0;
  int32_t m_ = 0;
  std::vector<std::vector<Edge>> edges_;

 public:
  Graph() = default;
  Graph(int32_t, int32_t);
  void DFS(std::vector<Vertex>&);
  void RecursiveDfsVisit(Vertex, Vertex, std::vector<Vertex>&, std::vector<int32_t>&, std::vector<int32_t>&,
                         std::vector<Color>&, int32_t&);
  friend std::istream& operator>>(std::istream&, Graph&);
};

Graph::Graph(int32_t n, int32_t m) : n_(n), m_(m), edges_(n + 1) {
}

void Graph::RecursiveDfsVisit(Vertex vertex, Vertex parent, std::vector<Vertex>& bridges, std::vector<int32_t>& time_in,
                              std::vector<int32_t>& time_out, std::vector<Color>& color, int32_t& curr_time) {
  color[vertex] = Color::kGray;
  time_in[vertex] = time_out[vertex] = ++curr_time;

  for (const auto& edge : edges_[vertex]) {
    if (edge.first != parent) {
      if (color[edge.first] == Color::kGray) {
        time_out[vertex] = std::min(time_out[vertex], time_in[edge.first]);
      }
      if (color[edge.first] == Color::kWhite) {
        RecursiveDfsVisit(edge.first, vertex, bridges, time_in, time_out, color, curr_time);
        time_out[vertex] = std::min(time_out[edge.first], time_out[vertex]);
        if (time_in[vertex] < time_out[edge.first]) {
          int32_t count = 0;
          for (const auto& k : edges_[vertex]) {
            if (k.first == edge.first) {
              ++count;
            }
          }
          if (count == 1) {
            bridges.emplace_back(edge.second);
          }
        }
      }
    }
  }
  color[vertex] = Color::kBlack;
}

void Graph::DFS(std::vector<int32_t>& bridges) {
  std::vector<Color> color(n_ + 1, Color::kWhite);
  std::vector<int32_t> time_in(n_ + 1, 0);
  std::vector<int32_t> time_out(n_ + 1, 0);
  int32_t curr_time = 0;
  for (Vertex vertex = 1; vertex < n_ + 1; ++vertex) {
    if (color[vertex] == Color::kWhite) {
      RecursiveDfsVisit(vertex, 0, bridges, time_in, time_out, color, curr_time);
    }
  }
}

std::istream& operator>>(std::istream& io, Graph& graph) {
  io >> graph.n_ >> graph.m_;
  graph.edges_.resize(graph.n_ + 1);
  for (int32_t i = 1; i < graph.m_ + 1; ++i) {
    Vertex begin = 0;
    Vertex end = 0;
    io >> begin >> end;
    graph.edges_[begin].emplace_back(std::make_pair(end, i));
    graph.edges_[end].emplace_back(std::make_pair(begin, i));
  }
  return io;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cin.tie(nullptr);
  Graph graph;
  std::cin >> graph;
  std::vector<Vertex> bridges;
  graph.DFS(bridges);
  std::cout << bridges.size() << "\n";
  std::sort(bridges.begin(), bridges.end());
  for (const auto& elem : bridges) {
    std::cout << elem << "\n";
  }
  return 0;
}
