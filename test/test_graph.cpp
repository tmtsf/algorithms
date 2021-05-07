#include "gtest/gtest.h"
#include "graph.hpp"
#include "util.hpp"

namespace cheetah
{
  namespace test
  {
    TEST(test_graph, DFSPaths)
    {
      std::cout << "**********************************************\n";
      std::vector<std::pair<int, int>> edges;
      int n;
      cheetah::util::parse_unweighted_graph("data/tiny_graph.txt", edges, n);

      graph_ptr_t g = cheetah::graph::make_undirected_graph(n);
      for (const auto& p : edges)
        g->add_edge(p.first, p.second);

      cheetah::int_vec_coll_t result = cheetah::single_source_paths_dfs(g, 0);
      for (int i=0; i<result.size(); ++i)
      {
        std::cout << i << ": ";
        for (int v : result[i])
          std::cout << v << "  ";
        std::cout << "\n";
      }
      std::cout << "**********************************************\n\n";
    }

    TEST(test_graph, BFSPaths)
    {
      std::cout << "**********************************************\n";
      std::vector<std::pair<int, int>> edges;
      int n;
      cheetah::util::parse_unweighted_graph("data/tiny_graph.txt", edges, n);

      graph_ptr_t g = cheetah::graph::make_undirected_graph(n);
      for (const auto& p : edges)
        g->add_edge(p.first, p.second);

      cheetah::int_vec_coll_t result = cheetah::single_source_paths_bfs(g, 0);
      for (int i=0; i<result.size(); ++i)
      {
        std::cout << i << ": ";
        for (int v : result[i])
          std::cout << v << "  ";
        std::cout << "\n";
      }
      std::cout << "**********************************************\n\n";
    }
  }
}
