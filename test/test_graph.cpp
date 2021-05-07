#include "gtest/gtest.h"
#include "graph.hpp"
#include "util.hpp"
#include "stack.hpp"
#include "queue.hpp"

namespace cheetah
{
  namespace test
  {
    namespace
    {
      void dfs(const std::vector<cheetah::bag<cheetah::edge>>& adj_list,
              int source,
              cheetah::bool_vec_t& visited,
              cheetah::int_vec_t& prev)
      {
        visited[source] = true;
        for (const auto& e : adj_list[source])
        {
          if (!visited[e.vertex])
          {
            prev[e.vertex] = source;
            dfs(adj_list, e.vertex, visited, prev);
          }
        }
      }

      cheetah::int_vec_coll_t single_source_paths_dfs(const cheetah::graph_ptr_t& g,
                                                      int source)
      {
        int n = g->number_of_vertices();
        cheetah::bool_vec_t visited(n, false);
        cheetah::int_vec_t prev(n, -1);

        const auto& adj_list = g->adjacency_list();
        dfs(adj_list, source, visited, prev);

        cheetah::int_vec_coll_t result(n, cheetah::int_vec_t());
        for (int i = 0; i < n; ++i)
        {
          if (i == source)
          {
            result[i].push_back(i);
          }
          else if (visited[i])
          {
            cheetah::stack<int> s;
            int vertex = i;
            s.push(vertex);
            while (prev[vertex] != source)
            {
              vertex = prev[vertex];
              s.push(vertex);
            }
            s.push(source);

            while (!s.empty())
            {
              vertex = s.top();
              s.pop();
              result[i].push_back(vertex);
            }
          }
        }

        return result;
      }

      cheetah::int_vec_coll_t single_source_paths_bfs(const cheetah::graph_ptr_t& g,
                                                      int source)
      {
        const auto& adj_list = g->adjacency_list();
        int n = g->number_of_vertices();
        cheetah::bool_vec_t visited(n, false);
        cheetah::int_vec_t prev(n, -1);

        cheetah::queue<int> q;
        q.push(source);
        visited[source] = true;
        while (!q.empty())
        {
          int v = q.front();
          q.pop();
          for (const auto& e : adj_list[v])
          {
            if (!visited[e.vertex])
            {
              q.push(e.vertex);
              visited[e.vertex] = true;
              prev[e.vertex] = v;
            }
          }
        }

        cheetah::int_vec_coll_t result(n, cheetah::int_vec_t());
        for (int i = 0; i < n; ++i)
        {
          if (i == source)
          {
            result[i].push_back(i);
          }
          else if (visited[i])
          {
            cheetah::stack<int> s;
            int vertex = i;
            s.push(vertex);
            while (prev[vertex] != source)
            {
              vertex = prev[vertex];
              s.push(vertex);
            }
            s.push(source);

            while (!s.empty())
            {
              vertex = s.top();
              s.pop();
              result[i].push_back(vertex);
            }
          }
        }

        return result;
      }
    }

    TEST(test_graph, DFSPaths)
    {
      std::cout << "**********************************************\n";
      std::vector<std::pair<int, int>> edges;
      int n;
      cheetah::util::parse_unweighted_graph("data/tiny_graph.txt", edges, n);

      graph_ptr_t g = cheetah::graph::make_undirected_graph(n);
      for (const auto& p : edges)
        g->add_edge(p.first, p.second);

      cheetah::int_vec_coll_t result = single_source_paths_dfs(g, 0);
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

      cheetah::int_vec_coll_t result = single_source_paths_bfs(g, 0);
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
