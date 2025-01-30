#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using Vertex = int32_t;
using Weight = int32_t;
using Edge = std::pair<Weight, Vertex>;
using AdjList = std::vector<std::vector<std::pair<Vertex, Weight>>>;
const auto kInf = std::numeric_limits<int32_t>::max();

class Graph {
  int32_t n_ = 0;
  int32_t m_ = 0;
  AdjList adj_;

 public:
  Graph() = default;
  Graph(int32_t, int32_t);
  int32_t Prim();
  friend std::istream& operator>>(std::istream&, Graph&);
};

Graph::Graph(int32_t n, int32_t m) : n_(n), m_(m) {
  adj_.resize(n + 1);
}

int32_t Graph::Prim() {
  Vertex start = 1;
  int32_t min_weight = 0;
  std::vector<int32_t> dist(n_ + 1, kInf);
  std::vector<bool> visited(n_ + 1, false);

  dist[start] = 0;
  std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> queue;
  Edge edge = std::make_pair(0, start);
  queue.emplace(edge);

  while (!queue.empty()) {
    Vertex vertex = queue.top().second;
    Weight weight = queue.top().first;
    queue.pop();

    if (!visited[vertex]) {
      visited[vertex] = true;
      min_weight += weight;
      for (const auto& neigh : adj_[vertex]) {
        if (!visited[neigh.first] && dist[neigh.first] > neigh.second) {
          dist[neigh.first] = neigh.second;
          Edge edge = std::make_pair(neigh.second, neigh.first);
          queue.emplace(edge);
        }
      }
    }
  }
  return min_weight;
}

std::istream& operator>>(std::istream& io, Graph& graph) {
  for (int32_t i = 0; i < graph.m_; ++i) {
    Vertex begin = 0;
    Vertex end = 0;
    Weight weight = 0;
    io >> begin >> end >> weight;
    graph.adj_[begin].emplace_back(std::make_pair(end, weight));
    graph.adj_[end].emplace_back(std::make_pair(begin, weight));
  }
  return io;
}

int main() {
  int32_t n = 0;
  int32_t m = 0;
  std::cin >> n >> m;
  Graph graph(n, m);
  std::cin >> graph;
  std::cout << graph.Prim() << "\n";
  return 0;
}
