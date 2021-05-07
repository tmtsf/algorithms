#include "gtest/gtest.h"
#include "graph.hpp"
#include "util.hpp"

namespace cheetah
{
  namespace test
  {
    TEST(test_undirected_graph, ConnectedComponents)
    {
      std::cout << "**********************************************\n";
      std::vector<std::pair<int, int>> edges;
      int n;
      cheetah::util::parse_unweighted_graph("data/tiny_graph.txt", edges, n);

      graph_ptr_t g = cheetah::graph::make_undirected_graph(n);
      for (const auto& p : edges)
        g->add_edge(p.first, p.second);

      cheetah::int_vec_t components = cheetah::undirected_graph_connected_components(g);

      std::unordered_map<int, std::vector<int>> result;
      for (int i=0; i<components.size(); ++i)
      {
        result[components[i]].push_back(i);
      }

      for (int i=0; i<result.size(); ++i)
      {
        std::cout << i << ": ";
        for (int v : result[i])
          std::cout << v << "  ";
        std::cout << "\n";
      }
      std::cout << "**********************************************\n\n";
    }


    TEST(test_kosaraju_strong_components, Components)
    {
      std::cout << "**********************************************\n";
      int n;
      std::vector<std::pair<int, int>> edges;
      cheetah::util::parse_unweighted_graph("data/tiny_digraph.txt", edges, n);

      graph_ptr_t g = cheetah::graph::make_directed_graph(n);
      for (const auto& p : edges)
        g->add_edge(p.first, p.second);

      cheetah::int_vec_t components = cheetah::kosaraju_strong_components(g);

      std::unordered_map<int, std::vector<int>> result;
      for (int i=0; i<components.size(); ++i)
      {
        result[components[i]].push_back(i);
      }

      for (int i=0; i<result.size(); ++i)
      {
        std::cout << i << ": ";
        for (int v : result[i])
          std::cout << v << "  ";
        std::cout << "\n";
      }
      std::cout << "**********************************************\n\n";
    }

    TEST(test_tarjan_strong_components, Components)
    {
      std::cout << "**********************************************\n";
      int n;
      std::vector<std::pair<int, int>> edges;
      cheetah::util::parse_unweighted_graph("data/tiny_digraph.txt", edges, n);

      graph_ptr_t g = cheetah::graph::make_directed_graph(n);
      for (const auto& p : edges)
        g->add_edge(p.first, p.second);

      std::vector<std::vector<int>> scc = cheetah::tarjan_strong_components(g);
      for (std::size_t i=0; i<scc.size(); ++i)
      {
        std::cout << i << ": ";
        for (const auto& vertex : scc[i])
          std::cout << vertex << " ";
        std::cout << "\n";
      }
      std::cout << "**********************************************\n\n";
    }
  }
}
