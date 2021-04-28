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
}
