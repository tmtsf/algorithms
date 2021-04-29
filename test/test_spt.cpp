#include "gtest/gtest.h"
#include "graph.hpp"
#include "util.hpp"

namespace cheetah
{
  namespace test
  {
    TEST(test_lazy_dijkstra_spt, SPT)
    {
      std::cout << "**********************************************\n";
      int n;
      std::vector<std::tuple<int, int, double>> edges;
      util::parse_weighted_graph("data/tiny_edge_weighted_digraph.txt", edges, n);

      graph_ptr_t g = cheetah::graph::make_directed_graph(n);
      for (const auto& p : edges)
        g->add_edge(std::get<0>(p), std::get<1>(p), std::get<2>(p));

      int source = 0;
      std::vector<cheetah::weighted_edge> spt = cheetah::lazy_dijkstra_spt(g, source);
      for (int i=0; i<n; ++i)
      {
        std::cout << source << " to " << i << ": ";
        cheetah::stack<weighted_edge> s;
        auto temp = spt[i];
        while (std::get<0>(temp) != -1)
        {
          s.push(temp);
          temp = spt[std::get<0>(temp)];
        }

        for (const auto& e : s)
        {
          std::cout << std::get<0>(e) << "->" << std::get<1>(e) << " " << std::get<2>(e) << " ";
        }

        std::cout << "\n";
      }
    }

    TEST(test_eager_dijkstra_spt, SPT)
    {
      std::cout << "**********************************************\n";
      int n;
      std::vector<std::tuple<int, int, double>> edges;
      util::parse_weighted_graph("data/tiny_edge_weighted_digraph.txt", edges, n);

      graph_ptr_t g = cheetah::graph::make_directed_graph(n);
      for (const auto& p : edges)
        g->add_edge(std::get<0>(p), std::get<1>(p), std::get<2>(p));

      int source = 0;
      std::vector<cheetah::weighted_edge> spt = cheetah::eager_dijkstra_spt(g, source);
      for (int i=0; i<n; ++i)
      {
        std::cout << source << " to " << i << ": ";
        cheetah::stack<weighted_edge> s;
        auto temp = spt[i];
        while (std::get<0>(temp) != -1)
        {
          s.push(temp);
          temp = spt[std::get<0>(temp)];
        }

        for (const auto& e : s)
        {
          std::cout << std::get<0>(e) << "->" << std::get<1>(e) << " " << std::get<2>(e) << " ";
        }

        std::cout << "\n";
      }
    }

    TEST(test_acyclic_spt, SPT)
    {
      std::cout << "**********************************************\n";
      int n;
      std::vector<std::tuple<int, int, double>> edges;
      util::parse_weighted_graph("data/tiny_edge_weighted_acyclic_digraph.txt", edges, n);

      graph_ptr_t g = cheetah::graph::make_directed_graph(n);
      for (const auto& p : edges)
        g->add_edge(std::get<0>(p), std::get<1>(p), std::get<2>(p));

      std::cout << "The topological order is:\n";
      std::vector<int> topo_order = cheetah::topological_sort(g);
      for (int i : topo_order)
        std::cout << i << "\t";
      std::cout << "\n\n";

      int source = topo_order.front();
      std::vector<cheetah::weighted_edge> spt = cheetah::acyclic_spt(g, source);
      for (int i : topo_order)
      {
        std::cout << source << " to " << i << ": ";
        cheetah::stack<weighted_edge> s;
        auto temp = spt[i];
        while (std::get<0>(temp) != -1)
        {
          s.push(temp);
          temp = spt[std::get<0>(temp)];
        }

        for (const auto& e : s)
        {
          std::cout << std::get<0>(e) << "->" << std::get<1>(e) << " " << std::get<2>(e) << " ";
        }

        std::cout << "\n";
      }

      std::cout << "**********************************************\n\n";
    }

    TEST(test_bellman_ford_spt, SPT)
    {
      std::cout << "**********************************************\n";
      std::vector<std::tuple<int, int, double>> edges;
      int n;
      util::parse_weighted_graph("data/tiny_edge_weighted_digraph.txt", edges, n);

      graph_ptr_t g = cheetah::graph::make_directed_graph(n);
      for (const auto& p : edges)
        g->add_edge(std::get<0>(p), std::get<1>(p), std::get<2>(p));

      int source = 0;
      std::vector<cheetah::weighted_edge> spt = cheetah::bellman_ford_spt(g, source);
      for (int i=0; i<n; ++i)
      {
        std::cout << source << " to " << i << ": ";
        cheetah::stack<weighted_edge> s;
        auto temp = spt[i];
        while (std::get<0>(temp) != -1)
        {
          s.push(temp);
          temp = spt[std::get<0>(temp)];
        }

        for (const auto& e : s)
        {
          std::cout << std::get<0>(e) << "->" << std::get<1>(e) << " " << std::get<2>(e) << " ";
        }

        std::cout << "\n";
      }

      std::cout << "**********************************************\n\n";
    }
  }
}
