#include "gtest/gtest.h"
#include "graph.hpp"
#include "util.hpp"

namespace cheetah
{
  namespace test
  {
    TEST(test_undirected_graph, CycleDetection)
    {
      std::cout << "**********************************************\n";
      std::vector<std::pair<int, int>> edges;
      int n;
      cheetah::util::parse_unweighted_graph("../data/tiny_graph.txt", edges, n);

      graph_ptr_t g = cheetah::graph::make_undirected_graph(n);
      for (const auto& p : edges)
        g->add_edge(p.first, p.second);

      bool result = cheetah::is_undirected_acyclic_graph(g);

      std::cout << "The graph is ";
      if (result)
        std::cout << "not ";
      std::cout << "cyclic!\n";
      std::cout << "**********************************************\n\n";
    }

    TEST(test_undirected_graph, Bipartite)
    {
      std::cout << "**********************************************\n";
      std::vector<std::pair<int, int>> edges;
      int n;
      cheetah::util::parse_unweighted_graph("../data/tiny_graph.txt", edges, n);

      graph_ptr_t g = cheetah::graph::make_undirected_graph(n);
      for (const auto& p : edges)
        g->add_edge(p.first, p.second);

      bool result = cheetah::is_undirected_bipartite_graph(g);
      std::cout << "The graph is ";
      if (!result)
        std::cout << "not ";
      std::cout << "bipartite!\n";
      std::cout << "**********************************************\n\n";
    }
  }
}
