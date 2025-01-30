#include <iostream>
#include <vector>

using Vertex = int;
enum class Color { kWhite, kGray, kBlack };

class Graph {
 public:
  int n = 0;
  int m = 0;
  std::vector<std::vector<Vertex>> adj;

  Graph() = default;
  Graph(const int&, const int&);
  void DFS(std::vector<int>&, std::vector<int>&, int&);
  void RecursiveDfsVisit(Vertex, std::vector<Color>&, std::vector<int>&, int&);
  void TopSort(std::vector<Vertex>&);
  void RecursiveTopSort(Vertex, std::vector<Color>&, std::vector<Vertex>&);
  friend std::istream& operator>>(std::istream&, Graph&);
};

Graph::Graph(const int& n, const int& m) : n(n), m(m), adj(n + 1) {
}

void Graph::RecursiveDfsVisit(Vertex vertex, std::vector<Color>& color, std::vector<int>& components, int& count) {
  color[vertex] = Color::kGray;
  components[vertex] = count;
  for (auto edge : adj[vertex]) {
    if (color[edge] == Color::kWhite) {
      RecursiveDfsVisit(edge, color, components, count);
    }
  }
  color[vertex] = Color::kBlack;
}

void Graph::DFS(std::vector<int>& order, std::vector<int>& components, int& count) {
  std::vector<Color> color(n + 1, Color::kWhite);
  for (auto i = static_cast<int>(order.size() - 1); i >= 0; --i) {
    if (color[order[i]] == Color::kWhite) {
      RecursiveDfsVisit(order[i], color, components, count);
      ++count;
    }
  }
}

void Graph::RecursiveTopSort(Vertex vertex, std::vector<Color>& color, std::vector<Vertex>& top_sorted) {
  color[vertex] = Color::kGray;
  for (auto edge : adj[vertex]) {
    if (color[edge] == Color::kWhite) {
      RecursiveTopSort(edge, color, top_sorted);
    }
  }
  top_sorted.emplace_back(vertex);
  color[vertex] = Color::kBlack;
}

void Graph::TopSort(std::vector<Vertex>& top_sorted) {
  std::vector<Color> color(n + 1, Color::kWhite);
  for (Vertex vertex = 1; vertex < n + 1; ++vertex) {
    if (color[vertex] == Color::kWhite) {
      RecursiveTopSort(vertex, color, top_sorted);
    }
  }
}

std::istream& operator>>(std::istream& io, Graph& graph) {
  io >> graph.n >> graph.m;
  graph.adj.resize(graph.n + 1);
  for (int i = 0; i < graph.m; ++i) {
    Vertex begin = 0;
    Vertex end = 0;
    io >> begin >> end;
    graph.adj[begin].emplace_back(end);
  }
  return io;
}

int main() {
  Graph graph;
  std::cin >> graph;
  Graph transposed_graph;
  transposed_graph.adj.resize(graph.adj.size());
  transposed_graph.n = graph.n + 1;
  for (size_t i = 0; i < graph.adj.size(); ++i) {
    for (size_t j = 0; j < graph.adj[i].size(); ++j) {
      transposed_graph.adj[graph.adj[i][j]].emplace_back(static_cast<int>(i));
    }
  }
  std::vector<int> top_sorted;
  std::vector<int> components(graph.n + 1);
  int count = 1;
  graph.TopSort(top_sorted);
  transposed_graph.DFS(top_sorted, components, count);
  std::cout << count - 1 << "\n";
  for (size_t i = 1; i < components.size(); ++i) {
    std::cout << components[i] << " ";
  }
  return 0;
}
