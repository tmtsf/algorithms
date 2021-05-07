#include "gtest/gtest.h"
#include "graph.hpp"
#include "util.hpp"

namespace cheetah
{
  namespace test
  {
    namespace
    {
      void hasCycle(const std::vector<cheetah::bag<cheetah::edge>>& adj_list,
                    cheetah::bool_vec_t& visited,
                    int curr,
                    int prev,
                    bool& result)
      {
        visited[curr] = true;
        for (const auto& e : adj_list[curr])
        {
          if (!visited[e.vertex])
            hasCycle(adj_list, visited, e.vertex, curr, result);
          else if (e.vertex != prev)
            result = true;
        }
      }
    }

    TEST(test_undirected_graph, CycleDetection)
    {
      std::cout << "**********************************************\n";
      std::vector<std::pair<int, int>> edges;
      int n;
      cheetah::util::parse_unweighted_graph("data/tiny_graph.txt", edges, n);

      graph_ptr_t g = cheetah::graph::make_undirected_graph(n);
      for (const auto& p : edges)
        g->add_edge(p.first, p.second);

      const auto& adj_list = g->adjacency_list();
      bool result(false);
      cheetah::bool_vec_t visited(n, false);
      for (int i = 0; i < n; ++i)
      {
        if (!visited[i])
          hasCycle(adj_list, visited, i, i, result);
      }

      std::cout << "The graph ";
      if (result)
        std::cout << "has ";
      else
        std::cout << "doesn't have ";
      std::cout << "a cycle!\n";
      std::cout << "**********************************************\n\n";
    }

    namespace
    {
      void isBipartite(const std::vector<cheetah::bag<cheetah::edge>>& adj_list,
                       cheetah::bool_vec_t& visited,
                       cheetah::bool_vec_t& color,
                       int v,
                       bool& result)
      {
        visited[v] = true;
        for (const auto& e : adj_list[v])
        {
          if (!visited[e.vertex])
          {
            color[e.vertex] = !color[v];
            isBipartite(adj_list, visited, color, e.vertex, result);
          }
          else if (color[e.vertex] == color[v])
            result = false;
        }
      }
    }

    TEST(test_undirected_graph, Bipartite)
    {
      std::cout << "**********************************************\n";
      std::vector<std::pair<int, int>> edges;
      int n;
      cheetah::util::parse_unweighted_graph("data/tiny_graph.txt", edges, n);

      graph_ptr_t g = cheetah::graph::make_undirected_graph(n);
      for (const auto& p : edges)
        g->add_edge(p.first, p.second);

      const auto& adj_list = g->adjacency_list();
      bool result(false);
      cheetah::bool_vec_t visited(n, false);
      cheetah::bool_vec_t color(n, false);
      for (int i = 0; i < n; ++i)
      {
        if (!visited[i])
          isBipartite(adj_list, visited, color, i, result);
      }

      std::cout << "The graph is ";
      if (!result)
        std::cout << "not ";
      std::cout << "bipartite!\n";
      std::cout << "**********************************************\n\n";
    }
  }
}
