#include "graph.hpp"

namespace cheetah
{
  edge::edge(void) :
    vertex(-1),
    weight(0)
  { }

  edge::edge(int vertex_,
             double weight_) :
    vertex(vertex_),
    weight(weight_)
  { }


  graph::graph(void) :
      n(0)
  { }

  graph::graph(int n_) :
    n(n_)
  { }

  int graph::number_of_vertices(void) const
  {
    return n;
  }

  void graph::print(void) const
  {
    for (int i = 0; i < n; ++i)
    {
      std::cout << i << ": ";
      for (const auto& edge : adjacency_list()[i])
        std::cout << edge.vertex << "  ";
      std::cout << "\n";
    }

    std::cout << "\n";
  }
}
