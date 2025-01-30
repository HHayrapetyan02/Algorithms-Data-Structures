#include <iostream>
#include <vector>
#include <queue>
#include <limits>

const auto kInf = std::numeric_limits<int>::max();

struct Vertex {
  int x = 0;
  int y = 0;
  int val = 0;
  bool flag = false;
  Vertex() : x(0), y(0), val(0), flag(false) {
  }
  Vertex(const int& x, const int& y, const int& val) : x(x), y(y), val(val), flag(false) {
  }
};

class Graph {
 public:
  int n = 0;
  int m = 0;
  std::vector<std::vector<Vertex>> adj;

  Graph() = default;
  explicit Graph(const int&, const int&);
  void Distance(std::vector<std::vector<int>>&);
};

Graph::Graph(const int& n, const int& m) : n(n), m(m), adj(n + 1, std::vector<Vertex>(m + 1)) {
}

void Graph::Distance(std::vector<std::vector<int>>& ans) {
  std::queue<Vertex> queue;
  for (int i = 1; i < n + 1; ++i) {
    for (int j = 1; j < m + 1; ++j) {
      int val = 0;
      std::cin >> val;
      if (val == 1) {
        auto curr = Vertex(j, i, 1);
        queue.emplace(curr);
        ans[i][j] = 0;
      } else {
        ans[i][j] = kInf;
      }
      adj[i][j] = {j, i, val};
    }
  }

  while (!queue.empty()) {
    Vertex vertex = queue.front();
    queue.pop();
    if (vertex.x - 1 >= 1 && !adj[vertex.y][vertex.x - 1].flag && adj[vertex.y][vertex.x - 1].val != 1) {
      adj[vertex.y][vertex.x - 1].flag = true;
      ans[vertex.y][vertex.x - 1] = ans[vertex.y][vertex.x] + 1;
      queue.emplace(adj[vertex.y][vertex.x - 1]);
    }
    if (vertex.x + 1 <= m && !adj[vertex.y][vertex.x + 1].flag && adj[vertex.y][vertex.x + 1].val != 1) {
      adj[vertex.y][vertex.x + 1].flag = true;
      ans[vertex.y][vertex.x + 1] = ans[vertex.y][vertex.x] + 1;
      queue.emplace(adj[vertex.y][vertex.x + 1]);
    }
    if (vertex.y - 1 >= 1 && !adj[vertex.y - 1][vertex.x].flag && adj[vertex.y - 1][vertex.x].val != 1) {
      adj[vertex.y - 1][vertex.x].flag = true;
      ans[vertex.y - 1][vertex.x] = ans[vertex.y][vertex.x] + 1;
      queue.emplace(adj[vertex.y - 1][vertex.x]);
    }
    if (vertex.y + 1 <= n && !adj[vertex.y + 1][vertex.x].flag && adj[vertex.y + 1][vertex.x].val != 1) {
      adj[vertex.y + 1][vertex.x].flag = true;
      ans[vertex.y + 1][vertex.x] = ans[vertex.y][vertex.x] + 1;
      queue.emplace(adj[vertex.y + 1][vertex.x]);
    }
  }
}

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  Graph graph(n, m);
  std::vector<std::vector<int>> ans(n + 1, std::vector<int>(m + 1));
  graph.Distance(ans);
  for (int i = 1; i < n + 1; ++i) {
    for (int j = 1; j < m + 1; ++j) {
      std::cout << ans[i][j] << " ";
    }
    std::cout << "\n";
  }
  return 0;
}
