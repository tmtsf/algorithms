#include "gtest/gtest.h"
#include "graph.hpp"
#include "util.hpp"

namespace cheetah
{
  namespace test
  {
    TEST(test_directed_graph, TopologicalSort)
    {
      std::cout << "**********************************************\n";
      std::vector<std::pair<int, int>> edges;
      std::unordered_map<std::string, int> lookup;
      std::vector<std::string> symbols;
      cheetah::util::parse_unweighted_graph("data/jobs.txt", "/", edges, lookup, symbols);

      graph_ptr_t g = cheetah::graph::make_directed_graph(symbols.size());
      for (const auto& p : edges)
        g->add_edge(p.first, p.second);

      std::vector<int> result = cheetah::topological_sort(g);
      for (const auto& i : result)
        std::cout << symbols[i] << "\n";
      std::cout << "**********************************************\n\n";
    }
  }
}
