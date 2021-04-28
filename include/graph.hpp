#pragma once

#include "fwd_decl.hpp"
#include "bag.hpp"
#include "stack.hpp"

namespace cheetah
{
  struct edge
  {
    edge(void);
    edge(int vertex_,
         double weight_);

    int vertex;
    double weight;
  };

  struct graph
  {
    graph(void);
    graph(int n_);
    virtual ~graph(void) = default;
  public:
    int number_of_vertices(void) const;
  public:
    virtual const std::string& description(void) const = 0;
    virtual const std::vector<cheetah::bag<edge>>& adjacency_list(void) const= 0;
    virtual cheetah::bag<weighted_edge> edges(void) const = 0;
    virtual void add_edge(int p, int q) = 0;
    virtual void add_edge(int p, int q, double weight) = 0;
  public:
    static cheetah::graph_ptr_t make_undirected_graph(int n);
    static cheetah::graph_ptr_t make_directed_graph(int n);
  private:
     int n;
  };

  namespace mixins
  {
    struct undirected
    {
      virtual ~undirected(void) = default;
    };

    struct directed
    {
      virtual ~directed(void) = default;
    public:
      virtual graph_ptr_t reverse(void) const = 0;
    };
  }

  std::vector<int> topological_sort(const cheetah::graph_ptr_t& g);

  void reverse_post_order(const cheetah::graph_ptr_t& g,
                          cheetah::stack<int>& s);

  cheetah::int_vec_coll_t undirected_graph_connected_components(const cheetah::graph_ptr_t& g);

  cheetah::int_vec_coll_t kosaraju_strong_components(const cheetah::graph_ptr_t& g);

  cheetah::int_vec_coll_t tarjan_strong_components(const cheetah::graph_ptr_t& g);
}
