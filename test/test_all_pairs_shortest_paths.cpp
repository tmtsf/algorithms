#include "gtest/gtest.h"
#include "graph.hpp"
#include "util.hpp"

namespace cheetah
{
  namespace test
  {
    TEST(test_graph, FloydWarshallAllPairsShortestPaths)
    {
      std::cout << "**********************************************\n";
      std::vector<std::tuple<int, int, double>> edges;
      int n;
      util::parse_weighted_graph("data/tiny_edge_weighted_graph.txt", edges, n);

      graph_ptr_t g = cheetah::graph::make_undirected_graph(n);
      for (const auto& p : edges)
        g->add_edge(std::get<0>(p), std::get<1>(p), std::get<2>(p));

      cheetah::dbl_mat_t shortest_paths = cheetah::floyd_warshall_shortest_paths(g);
      for (int i=0; i<n; ++i)
      {
        for (int j=0; j<n; ++j)
          printf("%1.2f    ", shortest_paths[i][j]);

        std::cout << "\n";
      }

      std::cout << "**********************************************\n\n";
    }
  }
}
