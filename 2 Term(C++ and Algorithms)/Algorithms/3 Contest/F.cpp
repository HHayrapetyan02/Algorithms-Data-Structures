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
  AdjList adj_;

 public:
  Graph() = default;
  explicit Graph(int32_t);
  int32_t Prim();
  friend std::istream& operator>>(std::istream&, Graph&);
};

Graph::Graph(int32_t n) : n_(n) {
  adj_.resize(n + 2);
}

int32_t Graph::Prim() {
  Vertex start = 1;
  int32_t min_weight = 0;
  std::vector<int32_t> dist(n_ + 2, kInf);
  std::vector<bool> visited(n_ + 2, false);

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
  for (int32_t i = 1; i < graph.n_ + 1; ++i) {
    for (int32_t j = 1; j < graph.n_ + 1; ++j) {
      Weight weight = 0;
      io >> weight;
      if (i != j) {
        graph.adj_[i].emplace_back(std::make_pair(j, weight));
      }
    }
  }
  for (int32_t i = 1; i < graph.n_ + 1; ++i) {
    Weight weight = 0;
    io >> weight;
    graph.adj_[i].emplace_back(std::make_pair(graph.n_ + 1, weight));
    graph.adj_[graph.n_ + 1].emplace_back(std::make_pair(i, weight));
  }
  return io;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int32_t n = 0;
  std::cin >> n;
  Graph graph(n);
  std::cin >> graph;
  std::cout << graph.Prim() << "\n";
  return 0;
}
