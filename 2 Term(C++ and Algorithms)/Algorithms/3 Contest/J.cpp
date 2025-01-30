#include <iostream>
#include <vector>
#include <queue>
#include <limits>

const auto kInf = std::numeric_limits<int32_t>::max();

struct Graph {
  int32_t n = 0;
  std::vector<std::vector<std::pair<int32_t, int32_t>>> edges;
  Graph() = default;
  explicit Graph(const int32_t& n) : n(n) {
    edges.resize(n + 1);
  }
  friend std::istream& operator>>(std::istream&, Graph&);
};

void Dijkstra(const Graph& graph, const int32_t& vertex, std::vector<int32_t>& dist) {
  dist[vertex] = 0;
  std::priority_queue<std::pair<int32_t, int32_t>, std::vector<std::pair<int32_t, int32_t>>,
                      std::greater<std::pair<int32_t, int32_t>>>
      queue;
  queue.emplace(0, vertex);
  while (!queue.empty()) {
    int32_t vertex = queue.top().second;
    int32_t weight = queue.top().first;
    queue.pop();
    if (weight <= dist[vertex]) {
      for (const auto& neigh : graph.edges[vertex]) {
        if (dist[neigh.first] > dist[vertex] + neigh.second) {
          dist[neigh.first] = dist[vertex] + neigh.second;
          queue.emplace(dist[neigh.first], neigh.first);
        }
      }
    }
  }
}

std::istream& operator>>(std::istream& io, Graph& graph) {
  for (int32_t i = 1; i < graph.n + 1; ++i) {
    for (int32_t j = 1; j < graph.n + 1; ++j) {
      int32_t weight = 0;
      io >> weight;
      if (weight > 0) {
        graph.edges[i].emplace_back(std::make_pair(j, weight));
      }
    }
  }
  return io;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int32_t n = 0;
  int32_t begin = 0;
  int32_t end = 0;
  std::cin >> n >> begin >> end;
  Graph graph(n);
  std::cin >> graph;
  std::vector<int32_t> dist(n + 1, kInf);
  Dijkstra(graph, begin, dist);
  std::cout << (dist[end] == kInf ? -1 : dist[end]) << "\n";
  return 0;
}
