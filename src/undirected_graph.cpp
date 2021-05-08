#include "graph.hpp"

namespace cheetah
{
  namespace
  {
    struct undirected_graph : public graph,
                              public mixins::undirected
    {
      undirected_graph(int n) :
        graph(n)
      {
        adj_list.resize(n);
      }
    public:
      virtual const std::string& description(void) const
      {
        static std::string ss("UndirectedGraph");
        return ss;
      }
      virtual const std::vector<cheetah::bag<edge>>& adjacency_list(void) const
      {
        return adj_list;
      }
      virtual cheetah::bag<weighted_edge> edges(void) const
      {
        cheetah::bag<weighted_edge> result;
        int n = number_of_vertices();
        for (int i=0; i<n; ++i)
        {
          for (const auto& e : adj_list[i])
          {
            if (e.vertex > i)
              result.push(std::make_tuple(i, e.vertex, e.weight));
          }
        }

        return result;
      }
      virtual void add_edge(int p, int q)
      {
        add_edge(p, q, 1.);
      }
      virtual void add_edge(int p, int q, double weight)
      {
        adj_list[p].push({q, weight});
        adj_list[q].push({p, weight});
      }
    private:
      std::vector<cheetah::bag<edge>> adj_list;
    };
  }

  cheetah::graph_ptr_t graph::make_undirected_graph(int n)
  {
    return std::make_shared<undirected_graph>(n);
  }

  namespace
  {
    void cycle_dfs(const std::vector<cheetah::bag<cheetah::edge>>& adj_list,
                   cheetah::bool_vec_t& visited,
                   int curr,
                   int prev,
                   bool& result)
    {
      visited[curr] = true;
      for (const auto& e : adj_list[curr])
      {
        if (!visited[e.vertex])
          cycle_dfs(adj_list, visited, e.vertex, curr, result);
        else if (e.vertex != prev)
          result = true;
      }
    }
  }

  bool is_acyclic_undirected_graph(const cheetah::graph_ptr_t& g)
  {
    const auto& adj_list = g->adjacency_list();
    int n = g->number_of_vertices();
    bool has_cycle(false);
    cheetah::bool_vec_t visited(n, false);
    for (int i = 0; i < n; ++i)
    {
      if (!visited[i])
        cycle_dfs(adj_list, visited, i, i, has_cycle);
    }

    return !has_cycle;
  }

  namespace
  {
    void bipartite_dfs(const std::vector<cheetah::bag<cheetah::edge>>& adj_list,
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
          bipartite_dfs(adj_list, visited, color, e.vertex, result);
        }
        else if (color[e.vertex] == color[v])
          result = false;
      }
    }
  }

  bool is_bipartite_undirected_graph(const cheetah::graph_ptr_t& g)
  {
    const auto& adj_list = g->adjacency_list();
    int n = g->number_of_vertices();
    bool is_bipartite(true);
    cheetah::bool_vec_t visited(n, false);
    cheetah::bool_vec_t color(n, false);
    for (int i = 0; i < n; ++i)
    {
      if (!visited[i])
        bipartite_dfs(adj_list, visited, color, i, is_bipartite);
    }

    return is_bipartite;
  }
}
