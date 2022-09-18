#include "graph.hpp"
#include "queue.hpp"
#include "stack.hpp"
#include "priority_queue.hpp"
#include "indexed_priority_queue.hpp"
#include "util.hpp"

namespace cheetah
{
  namespace
  {
    void lazy_dijkstra_visit(const std::vector<cheetah::bag<edge>>& adj_list,
                             int i,
                             std::vector<double>& distance,
                             cheetah::priority_queue<weighted_edge, util::greater<weighted_edge>>& pq,
                             std::vector<weighted_edge>& spt)
    {
      for (const auto& e : adj_list[i])
      {
        int vertex = e.vertex;
        double weight = e.weight;
        if (distance[vertex] > distance[i] + weight)
        {
          distance[vertex] = distance[i] + weight;
          pq.push({i, vertex, weight});
          spt[vertex] = {i, vertex, weight};
        }
      }
    }

    void eager_dijkstra_visit(const std::vector<cheetah::bag<edge>>& adj_list,
                              int i,
                              std::vector<double>& distance,
                              cheetah::indexed_priority_queue<weighted_edge, util::greater<weighted_edge>>& pq,
                              std::vector<weighted_edge>& spt)
    {
      for (const auto& e : adj_list[i])
      {
        int vertex = e.vertex;
        double weight = e.weight;
        if (distance[vertex] > distance[i] + weight)
        {
          distance[vertex] = distance[i] + weight;
          spt[vertex] = {i, vertex, weight};
          if (pq.contains(vertex))
            pq.change(vertex, {i, vertex, weight});
          else
            pq.push(vertex, {i, vertex, weight});
        }
      }
    }
  }

  std::vector<weighted_edge> lazy_dijkstra_spt(const graph_ptr_t& g,
                                               int source)
  {
    util::validate_directed_graph(g);

    int n = g->number_of_vertices();
    const auto& adj_list = g->adjacency_list();

    std::vector<double> distance(n, DBL_MAX);
    cheetah::priority_queue<weighted_edge, util::greater<weighted_edge>> pq;
    std::vector<cheetah::weighted_edge> spt(n);

    distance[source] = 0.0;
    pq.push({-1, source, 0.0});
    spt[source] = {-1, source, 0.0};
    while (!pq.empty())
    {
      weighted_edge t = pq.top();
      pq.pop();
      lazy_dijkstra_visit(adj_list, std::get<1>(t), distance, pq, spt);
    }

    return spt;
  }

  std::vector<weighted_edge> eager_dijkstra_spt(const graph_ptr_t& g,
                                                int source)
  {
    util::validate_directed_graph(g);

    int n = g->number_of_vertices();
    const auto& adj_list = g->adjacency_list();

    std::vector<double> distance(n, DBL_MAX);
    cheetah::indexed_priority_queue<weighted_edge, util::greater<weighted_edge>> pq;
    std::vector<cheetah::weighted_edge> spt(n);

    distance[source] = 0;
    pq.push(source, {-1, source, 0.0});
    spt[source] = {-1, source, 0.0};
    while (!pq.empty())
    {
      weighted_edge t = pq.top();
      pq.pop();
      eager_dijkstra_visit(adj_list, std::get<1>(t), distance, pq, spt);
    }

    return spt;
  }

  std::vector<weighted_edge> acyclic_spt(const graph_ptr_t& g,
                                         int source)
  {
    if (!cheetah::is_directed_acyclic_graph(g))
      throw("The supplied directed graph is not acyclic");

    int n = g->number_of_vertices();
    const auto& adj_list = g->adjacency_list();

    std::vector<double> distance(n, DBL_MAX);
    std::vector<cheetah::weighted_edge> spt(n);

    std::vector<int> topo_order = cheetah::topological_sort(g);
    distance[topo_order.front()] = 0.0;
    spt[topo_order.front()] = {-1, source, 0.0};
    for (int i : topo_order)
    {
      for (const auto& e : adj_list[i])
      {
        int vertex = e.vertex;
        double weight = e.weight;
        if (distance[vertex] > distance[i] + weight)
        {
          distance[vertex] = distance[i] + weight;
          spt[vertex] = {i, vertex, weight};
        }
      }
    }

    return spt;
  }

  std::vector<weighted_edge> bellman_ford_spt(const graph_ptr_t& g,
                                              int source)
  {
    util::validate_directed_graph(g);

    int n = g->number_of_vertices();
    const auto& adj_list = g->adjacency_list();

    std::vector<double> distance(n, DBL_MAX);
    std::vector<bool> on_queue(n, false);
    cheetah:queue<int> q;
    std::vector<cheetah::weighted_edge> spt(n, {-1, -1, 0.0});
    int count = 0;
    bool negative_cycle(false);

    distance[source] = 0.0;
    q.push(source);
    on_queue[source] = true;
    spt[source] = {-1, source, 0.0};
    while (!q.empty() && !negative_cycle)
    {
      int t = q.front();
      q.pop();
      on_queue[t] = false;
      for (const auto& e : adj_list[t])
      {
        int w = e.vertex;
        if (distance[w] > distance[t] + e.weight)
        {
          distance[w] = distance[t] + e.weight;
          spt[w] = {t, w, e.weight};
          std::cout << t << "->" << w << "  " << e.weight << "\n";
          if (!on_queue[w])
          {
            q.push(w);
            on_queue[w] = true;
          }
        }

        if (count++ % n == 0)
        {
          graph_ptr_t cycle = cheetah::graph::make_directed_graph(n);
          for (const auto& we : spt)
          {
            if (std::get<0>(we) != -1)
              cycle->add_edge(std::get<0>(we), std::get<1>(we), std::get<2>(we));
          }

          negative_cycle = !cheetah::is_directed_acyclic_graph(cycle);
          if (negative_cycle)
            cycle->print();
        }
      }
    }

    return spt;
  }
}
