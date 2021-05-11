#include "graph.hpp"

namespace cheetah
{
  namespace
  {
    void connected_components_helper(const std::vector<cheetah::bag<edge>>& adj_list,
                                     int i,
                                     cheetah::bool_vec_t& visited,
                                     cheetah::int_vec_t& component,
                                     int count)
    {
      visited[i] = true;
      component[i] = count;
      const auto& vertices = adj_list[i];
      for (const auto& e : vertices)
      {
        if (!visited[e.vertex])
          connected_components_helper(adj_list, e.vertex, visited, component, count);
      }
    }
  }

  cheetah::int_vec_t undirected_graph_connected_components(const graph_ptr_t& g)
  {
    const auto& adj_list = g->adjacency_list();
    int n = g->number_of_vertices();
    cheetah::bool_vec_t visited(n);
    cheetah::int_vec_t components(n);

    int count = 0;
    for (int i=0; i<n; ++i)
    {
      if (!visited[i])
      {
        connected_components_helper(adj_list, i, visited, components, count);
        ++count;
      }
    }

    return components;
  }

  namespace
  {
    void kosaraju_strong_components_helper(const std::vector<cheetah::bag<edge>>& adj_list,
                                           int t,
                                           cheetah::bool_vec_t& visited,
                                           cheetah::int_vec_t& components,
                                           int count)
    {
      visited[t] = true;
      components[t] = count;
      for (const auto& e : adj_list[t])
      {
        if (!visited[e.vertex])
          kosaraju_strong_components_helper(adj_list, e.vertex, visited, components, count);
      }
    }
  }

  cheetah::int_vec_t kosaraju_strong_components(const graph_ptr_t& g)
  {
    auto pd = dynamic_cast<cheetah::mixins::directed*>(g.get());
    graph_ptr_t rev_graph = pd->reverse();
    cheetah::stack<int> s;
    reverse_post_order(rev_graph, s);

    const auto& adj_list = g->adjacency_list();
    int n = g->number_of_vertices();
    cheetah::bool_vec_t visited(n, false);
    cheetah::int_vec_t components(n);

    int count = 0;
    while (!s.empty())
    {
      int t = s.top();
      s.pop();
      if (!visited[t])
      {
        kosaraju_strong_components_helper(adj_list, t, visited, components, count);
        ++count;
      }
    }

    return components;
  }

  namespace
  {
    void tarjan_dfs(const std::vector<cheetah::bag<edge>>& adj_list,
                    int n,
                    int i,
                    cheetah::bool_vec_t& visited,
                    cheetah::int_vec_t& id,
                    cheetah::int_vec_t& low,
                    int& pre,
                    int& count,
                    cheetah::stack<int>& s)
    {
      visited[i] = true;
      low[i] = pre++;
      int min = low[i];
      s.push(i);
      for (const auto& e : adj_list[i])
      {
        if (!visited[e.vertex])
          tarjan_dfs(adj_list, n, e.vertex, visited, id, low, pre, count, s);
        if (low[e.vertex] < min)
          min = low[e.vertex];
      }

      if (min < low[i])
      {
        low[i] = min;
        return;
      }

      int w;
      do
      {
        w = s.top();
        s.pop();
        id[w] = count;
        low[w] = n;
      } while (w != i);

      ++count;
    }
  }

  cheetah::int_vec_coll_t tarjan_strong_components(const graph_ptr_t& g)
  {
    const auto& adj_list = g->adjacency_list();
    int n = g->number_of_vertices();

    cheetah::bool_vec_t visited(n, false);
    cheetah::int_vec_t id(n, 0);
    cheetah::int_vec_t low(n, 0);
    int pre{0};
    int count{0};
    cheetah::stack<int> s;
    for (int i = 0; i < n; ++i)
    {
      if (!visited[i])
        tarjan_dfs(adj_list, n, i, visited, id, low, pre, count, s);
    }

    cheetah::int_vec_coll_t results(count, cheetah::int_vec_t());
    for (int i = 0; i < n; ++i)
    {
      results[id[i]].push_back(i);
    }

    return results;
  }
}
