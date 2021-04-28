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

  cheetah::int_vec_coll_t undirected_graph_connected_components(const graph_ptr_t& g)
  {
    const auto& adj_list = g->adjacency_list();
    int n = g->number_of_vertices();
    cheetah::bool_vec_t visited(n);
    cheetah::int_vec_t component(n);

    int count = 0;
    for (int i=0; i<n; ++i)
    {
      if (!visited[i])
      {
        connected_components_helper(adj_list, i, visited, component, count);
        ++count;
      }
    }

    cheetah::int_vec_coll_t result(count);
    for (int i=0; i<component.size(); ++i)
    {
      result[component[i]].push_back(i);
    }

    return result;
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

  cheetah::int_vec_coll_t kosaraju_strong_components(const graph_ptr_t& g)
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

    cheetah::int_vec_coll_t results(count);
    for (std::size_t i=0; i<components.size(); ++i)
    {
      results[components[i]].push_back(i);
    }

    return results;
  }

  namespace
  {
    void tarjan_strong_components_helper(const std::vector<cheetah::bag<edge>>& adj_list,
                                         int i,
                                         cheetah::int_vec_t& stamps,
                                         cheetah::int_vec_t& lows,
                                         cheetah::stack<int>& s,
                                         cheetah::bool_vec_t& on_stack,
                                         int& stamp,
                                         cheetah::int_vec_coll_t& components)
    {
      stamps[i] = stamp;
      lows[i] = stamp;
      on_stack[i] = true;
      s.push(i);
      for (const auto& e : adj_list[i])
      {
        int j = e.vertex;
        if (!stamps[j])
        {
          tarjan_strong_components_helper(adj_list, j, stamps, lows, s, on_stack, ++stamp, components);
          if (lows[j] < lows[i])
            lows[i] = lows[j];
        }
        else if (on_stack[j] && stamps[j] < lows[i])
        {
          lows[i] = stamps[j];
        }
      }

      if (lows[i] == stamps[i])
      {
        cheetah::int_vec_t component;
        int t = 0;
        while (t != i)
        {
          t = s.top();
          s.pop();
          on_stack[t] = false;
          component.push_back(t);
        }
        components.push_back(component);
      }
    }
  }

  cheetah::int_vec_coll_t tarjan_strong_components(const graph_ptr_t& g)
  {
    const auto& adj_list = g->adjacency_list();
    int n = g->number_of_vertices();

    cheetah::int_vec_t stamps(n, 0);
    cheetah::int_vec_t lows(n, 0);
    cheetah::stack<int> s;
    cheetah::bool_vec_t on_stack(n, false);
    int count = 0;

    cheetah::int_vec_coll_t results;
    for (int i=0; i<n; ++i)
      if (!stamps[i])
        tarjan_strong_components_helper(adj_list, i, stamps, lows, s, on_stack, count, results);

    return results;
  }
}
