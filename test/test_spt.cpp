#include "gtest/gtest.h"
#include "graph.hpp"
#include "util.hpp"

namespace cheetah
{
  namespace test
  {
    // TEST(test_lazy_dijkstra_spt, SPT)
    // {
    //   std::cout << "**********************************************\n";
    //   int n;
    //   std::vector<std::tuple<int, int, double>> edges;
    //   util::parse_weighted_graph("data/medium_edge_weighted_digraph.txt", edges, n);

    //   graph_ptr_t g = cheetah::graph::make_directed_graph(n);
    //   for (const auto& p : edges)
    //     g->add_edge(std::get<0>(p), std::get<1>(p), std::get<2>(p));

    //   int source = 0;
    //   std::vector<cheetah::weighted_edge> spt = cheetah::lazy_dijkstra_spt(g, source);
    //   for (int i=0; i<n; ++i)
    //   {
    //     std::cout << source << " to " << i << ": ";
    //     cheetah::stack<weighted_edge> s;
    //     auto temp = spt[i];
    //     while (std::get<0>(temp) != -1)
    //     {
    //       s.push(temp);
    //       temp = spt[std::get<0>(temp)];
    //     }

    //     for (const auto& e : s)
    //     {
    //       std::cout << std::get<0>(e) << "->" << std::get<1>(e) << " " << std::get<2>(e) << " ";
    //     }

    //     std::cout << "\n";
    //   }
    // }

    // TEST(test_eager_dijkstra_spt, SPT)
    // {
    //   std::cout << "**********************************************\n";
    //   int n;
    //   std::vector<std::tuple<int, int, double>> edges;
    //   util::parse_weighted_graph("data/medium_edge_weighted_digraph.txt", edges, n);

    //   graph_ptr_t g = cheetah::graph::make_directed_graph(n);
    //   for (const auto& p : edges)
    //     g->add_edge(std::get<0>(p), std::get<1>(p), std::get<2>(p));

    //   int source = 0;
    //   std::vector<cheetah::weighted_edge> spt = cheetah::eager_dijkstra_spt(g, source);
    //   for (int i=0; i<n; ++i)
    //   {
    //     std::cout << source << " to " << i << ": ";
    //     cheetah::stack<weighted_edge> s;
    //     auto temp = spt[i];
    //     while (std::get<0>(temp) != -1)
    //     {
    //       s.push(temp);
    //       temp = spt[std::get<0>(temp)];
    //     }

    //     for (const auto& e : s)
    //     {
    //       std::cout << std::get<0>(e) << "->" << std::get<1>(e) << " " << std::get<2>(e) << " ";
    //     }

    //     std::cout << "\n";
    //   }
    // }
  }
}
