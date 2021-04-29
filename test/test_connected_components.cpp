#include "gtest/gtest.h"
#include "graph.hpp"
#include "util.hpp"

namespace cheetah
{
  namespace test
  {
    TEST(test_undirected_graph_connected_components, Components)
    {
      std::cout << "**********************************************\n";
      std::vector<std::pair<int, int>> edges;
      int n;
      cheetah::util::parse_unweighted_graph("data/medium_graph.txt", edges, n);

      graph_ptr_t g = cheetah::graph::make_undirected_graph(n);
      for (const auto& p : edges)
        g->add_edge(p.first, p.second);

      cheetah::int_vec_coll_t result = cheetah::undirected_graph_connected_components(g);
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
