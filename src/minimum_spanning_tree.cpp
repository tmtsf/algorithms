#include "queue.hpp"
#include "graph.hpp"
#include "union_find.hpp"
#include "priority_queue.hpp"
#include "indexed_priority_queue.hpp"
#include "util.hpp"

namespace cheetah
{
  namespace
  {
    void lazy_prim_visit(const std::vector<cheetah::bag<edge>>& adj_list,
                         int i,
                         std::vector<bool>& visited,
                         cheetah::priority_queue<weighted_edge, util::greater<weighted_edge>>& pq)
    {
      visited[i] = true;
      for (const auto& e : adj_list[i])
      {
        if (!visited[e.vertex])
          pq.push({i, e.vertex, e.weight});
      }
    }

    void eager_prim_visit(const std::vector<cheetah::bag<edge>>& adj_list,
                          int i,
                          std::vector<bool>& visited,
                          std::vector<double>& distance,
                          cheetah::indexed_priority_queue<weighted_edge, util::greater<weighted_edge>>& pq,
                          std::vector<weighted_edge>& mst)
    {
      visited[i] = true;
      for (const auto& e : adj_list[i])
      {
        int vertex = e.vertex;
        double weight = e.weight;
        if (visited[vertex])
        {
          continue;
        }
        if (weight < distance[vertex])
        {
          distance[vertex] = weight;
          if (pq.contains(vertex))
            pq.change(vertex, {i, vertex, weight});
          else
          {
            pq.push(vertex, {i, vertex, weight});
          }
          mst[vertex] = {i, vertex, weight};
        }
      }
    }
  }

  std::vector<weighted_edge> lazy_prim_mst(const graph_ptr_t& g)
  {
    // util::validate_undirected_graph(g);

    int n = g->number_of_vertices();
    const auto& adj_list = g->adjacency_list();
    std::vector<bool> visited(n, false);
    cheetah::priority_queue<weighted_edge, util::greater<weighted_edge>> pq;
    std::vector<weighted_edge> mst;

    lazy_prim_visit(adj_list, 0, visited, pq);
    while (!pq.empty())
    {
      auto e = pq.top();
      pq.pop();
      int u = std::get<0>(e);
      int w = std::get<1>(e);
      if (visited[u] && visited[w])
        continue;

      mst.push_back(e);
      if (!visited[u])
        lazy_prim_visit(adj_list, u, visited, pq);
      if (!visited[w])
        lazy_prim_visit(adj_list, w, visited, pq);
    }

    assert(mst.size() == n-1);
    return mst;
  }

  std::vector<weighted_edge> eager_prim_mst(const graph_ptr_t& g)
  {
    // util::validate_undirected_graph(g);

    int n = g->number_of_vertices();
    const auto& adj_list = g->adjacency_list();
    std::vector<bool> visited(n, false);
    std::vector<double> distance(n, DBL_MAX);
    cheetah::indexed_priority_queue<weighted_edge, util::greater<weighted_edge>> pq;
    std::vector<weighted_edge> mst(n);

    distance[0] = 0;
    pq.push(0, {0, 0, 0.0});
    while (!pq.empty())
    {
      weighted_edge t = pq.top();
      pq.pop();
      eager_prim_visit(adj_list, std::get<1>(t), visited, distance, pq, mst);
    }

    return std::vector<weighted_edge>(mst.cbegin() + 1U, mst.cend());
  }

  std::vector<weighted_edge> kruskal_mst(const graph_ptr_t& g)
  {
    // util::validate_undirected_graph(g);

    int n = g->number_of_vertices();
    const auto& adj_list = g->adjacency_list();

    cheetah::priority_queue<weighted_edge, util::greater<weighted_edge>> pq;
    auto edges = g->edges();
    for (const auto& e : edges)
      pq.push(e);

    std::vector<weighted_edge> mst;
    cheetah::union_find_ptr_t uf = cheetah::union_find::make_weighted_quick_union(n);
    while (!pq.empty() && mst.size() < n-1)
    {
      cheetah::weighted_edge e = pq.top();
      pq.pop();
      int u = std::get<0>(e);
      int v = std::get<1>(e);
      if (uf->connected(u, v))
        continue;

      uf->join(u, v);
      mst.push_back(e);
    }

    return mst;
  }
}
