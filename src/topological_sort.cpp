#include "graph.hpp"

namespace cheetah
{
  namespace
  {
    void is_dag_helper(const std::vector<cheetah::bag<edge>>& adj_list,
                       int v,
                       std::vector<bool>& visited,
                       std::vector<bool>& on_stack,
                       bool& result)
    {
      on_stack[v] = true;
      visited[v] = true;
      for (const auto& e : adj_list[v])
      {
        if (on_stack[e.vertex])
        {
          result = false;
          return;
        }
        else
          is_dag_helper(adj_list, e.vertex, visited, on_stack, result);
      }

      on_stack[v] = false;
    }
  }

  bool is_dag(const graph_ptr_t& g)
  {
    const auto& adj_list = g->adjacency_list();
    std::vector<bool> visited(g->number_of_vertices(), false);
    std::vector<bool> on_stack(g->number_of_vertices(), false);
    bool result(true);
    for (std::size_t i=0; i<adj_list.size(); ++i)
    {
      if (!visited[i])
        is_dag_helper(adj_list, i, visited, on_stack, result);
    }

    return result;
  }

  namespace
  {
    void reverse_post_order_helper(const std::vector<cheetah::bag<edge>>& adj_list,
                                   int v,
                                   std::vector<bool>& visited,
                                   cheetah::stack<int>& s)
    {
      visited[v] = true;
      for (const auto& e : adj_list[v])
      {
        if (!visited[e.vertex])
          reverse_post_order_helper(adj_list, e.vertex, visited, s);
      }

      s.push(v);
    }
  }

  void reverse_post_order(const graph_ptr_t& g,
                          cheetah::stack<int>& s)
  {
    const auto& adj_list = g->adjacency_list();
    std::vector<bool> visited(adj_list.size(),  false);
    for (std::size_t i=0; i<adj_list.size(); ++i)
    {
      if (!visited[i])
      {
        reverse_post_order_helper(adj_list, i, visited, s);
      }
    }
  }

  std::vector<int> topological_sort(const graph_ptr_t& g)
  {
    if (!is_dag(g))
    {
      std::cout << "Cannot perform topological sort on a directed graph with cycle!\n";
      exit(1);
    }

    cheetah::stack<int> s;
    reverse_post_order(g, s);

    std::vector<int> result;
    while (!s.empty())
    {
      result.push_back(s.top());
      s.pop();
    }

    return result;
  }
}
