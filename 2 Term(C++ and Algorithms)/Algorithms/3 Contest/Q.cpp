#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

struct Edge {
  int32_t begin = 0;
  int32_t end = 0;
  int32_t volume = 0;
  int32_t flow = 0;
  Edge() = default;
  Edge(const int32_t& begin, const int32_t& end, const int32_t& volume) : begin(begin), end(end), volume(volume) {
  }
};

struct Graph {
  int32_t n = 0;
  int32_t m = 0;
  std::vector<Edge> edges;
  std::vector<std::vector<int32_t>> values;
  Graph() = default;
  Graph(const int32_t& n, const int32_t& m) : n(n), m(m) {
    values.resize(n + 1);
    edges.resize(1);
  }
  friend std::istream& operator>>(std::istream&, Graph&);
};

bool BFS(Graph& graph, std::vector<int32_t>& level, int32_t start, int32_t finish) {
  std::queue<int32_t> queue;
  queue.emplace(start);
  while (!queue.empty()) {
    int32_t begin = queue.front();
    queue.pop();
    for (const auto& neighbour : graph.values[begin]) {
      Edge edge = graph.edges[neighbour];
      if (level[edge.end] == 0 && edge.end != start && edge.volume > edge.flow) {
        level[edge.end] = level[begin] + 1;
        queue.emplace(edge.end);
      }
    }
  }
  return level[finish] != 0;
}

int32_t ReverseAnswer(const Graph& graph, const int32_t& start, const int32_t& finish) {
  for (auto& reverse : graph.values[finish]) {
    if (graph.edges[reverse].end == start && graph.edges[reverse].begin == finish) {
      return reverse;
    }
  }
  return -1;
}

int32_t DFS(Graph& graph, std::vector<int32_t>& level, std::vector<int32_t>& parent, int32_t start, int32_t finish,
            int32_t tmp_flow) {
  if (start != finish && tmp_flow != 0) {
    for (size_t i = parent[start]; i < graph.values[start].size(); ++i) {
      Edge& edge = graph.edges[graph.values[start][i]];
      if (level[edge.end] == level[start] + 1 && edge.flow < edge.volume) {
        int32_t flow = DFS(graph, level, parent, edge.end, finish, std::min(tmp_flow, edge.volume - edge.flow));
        if (flow <= 0) {
          continue;
        }
        edge.flow += flow;
        int32_t reverse = ReverseAnswer(graph, start, edge.end);
        if (reverse != -1) {
          graph.edges[reverse].flow -= flow;
        }
        return flow;
      }
    }
    return 0;
  }
  return tmp_flow;
}

int32_t MaxFlow(Graph& graph, const int32_t& start, const int32_t& finish) {
  int32_t ans = 0;
  std::vector<int32_t> parent(graph.n + 1, 1);
  std::vector<int32_t> level(graph.n + 1, 0);
  while (BFS(graph, level, start, finish)) {
    std::fill(parent.begin(), parent.end(), 0);
    int32_t tmp_flow = 1;
    while (tmp_flow > 0) {
      tmp_flow = DFS(graph, level, parent, start, finish, 1e9);
      if (tmp_flow > 0) {
        ans += tmp_flow;
      }
    }
    std::fill(level.begin(), level.end(), 0);
  }
  return ans;
}

std::istream& operator>>(std::istream& is, Graph& graph) {
  for (int32_t i = 0; i < graph.m; ++i) {
    int32_t begin = 0;
    int32_t end = 0;
    int32_t volume = 0;
    is >> begin >> end >> volume;
    graph.edges.emplace_back(begin, end, volume);
    graph.edges.emplace_back(end, begin, 0);
    graph.values[begin].emplace_back(graph.edges.size() - 2);
    graph.values[end].emplace_back(graph.edges.size() - 1);
  }
  return is;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int32_t n = 0;
  int32_t m = 0;
  std::cin >> n >> m;
  int32_t start = 1;
  int32_t finish = n;
  Graph graph(n, m);
  std::cin >> graph;
  std::cout << MaxFlow(graph, start, finish) << "\n";
  return 0;
}
