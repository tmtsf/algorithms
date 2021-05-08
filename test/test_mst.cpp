#include "gtest/gtest.h"
#include "graph.hpp"
#include "util.hpp"

namespace cheetah
{
  namespace test
  {
    TEST(test_undirected_graph, LazyPrimMST)
    {
      std::cout << "**********************************************\n";
      int n;
      std::vector<std::tuple<int, int, double>> edges;
      util::parse_weighted_graph("data/tiny_edge_weighted_graph.txt", edges, n);

      graph_ptr_t g = cheetah::graph::make_undirected_graph(n);
      for (const auto& p : edges)
        g->add_edge(std::get<0>(p), std::get<1>(p), std::get<2>(p));

      std::vector<cheetah::weighted_edge> mst = cheetah::lazy_prim_mst(g);
      std::sort(mst.begin(),
                mst.end(),
                [](const auto&p1, const auto& p2)
                { return std::get<2>(p1) < std::get<2>(p2); });
      for (std::size_t i=0; i<mst.size(); ++i)
      {
        std::cout << std::get<0>(mst[i]) << "-"
                  << std::get<1>(mst[i]) << " "
                  << std::get<2>(mst[i]) << "\n";
      }
      std::cout << "**********************************************\n\n";
    }

    TEST(test_undirected_graph, EagerPrimMST)
    {
      std::cout << "**********************************************\n";
      int n;
      std::vector<std::tuple<int, int, double>> edges;
      util::parse_weighted_graph("data/tiny_edge_weighted_graph.txt", edges, n);

      graph_ptr_t g = cheetah::graph::make_undirected_graph(n);
      for (const auto& p : edges)
        g->add_edge(std::get<0>(p), std::get<1>(p), std::get<2>(p));

      std::vector<cheetah::weighted_edge> mst = cheetah::eager_prim_mst(g);
      std::sort(mst.begin(),
                mst.end(),
                [](const auto&p1, const auto& p2)
                { return std::get<2>(p1) < std::get<2>(p2); });
      for (std::size_t i=0; i<mst.size(); ++i)
      {
        std::cout << std::get<0>(mst[i]) << "-"
                  << std::get<1>(mst[i]) << " "
                  << std::get<2>(mst[i]) << "\n";
      }
      std::cout << "**********************************************\n\n";
    }

    TEST(test_undirected_graph, KruskalMST)
    {
      std::cout << "**********************************************\n";
      int n;
      std::vector<std::tuple<int, int, double>> edges;
      util::parse_weighted_graph("data/tiny_edge_weighted_graph.txt", edges, n);

      graph_ptr_t g = cheetah::graph::make_undirected_graph(n);
      for (const auto& p : edges)
        g->add_edge(std::get<0>(p), std::get<1>(p), std::get<2>(p));

      std::vector<cheetah::weighted_edge> mst = cheetah::kruskal_mst(g);
      std::sort(mst.begin(),
                mst.end(),
                [](const auto&p1, const auto& p2)
                { return std::get<2>(p1) < std::get<2>(p2); });
      for (std::size_t i=0; i<mst.size(); ++i)
      {
        std::cout << std::get<0>(mst[i]) << "-"
                  << std::get<1>(mst[i]) << " "
                  << std::get<2>(mst[i]) << "\n";
      }
      std::cout << "**********************************************\n\n";
    }
  }
}
