#include "graph.hpp"

namespace cheetah
{
  cheetah::dbl_mat_t floyd_warshall_shortest_paths(const cheetah::graph_ptr_t& g)
  {
    const auto& adj_list = g->adjacency_list();
    int n = g->number_of_vertices();
    cheetah::dbl_mat_t result = dbl_mat_t(n, dbl_vec_t(n, DBL_MAX));

    for (int i=0; i<n; ++i)
    {
      for (const auto& e : adj_list[i])
        result[i][e.vertex] = e.weight;

      result[i][i] = 0;
    }

    for (int k=0; k<n; ++k)
      for (int i=0; i<n; ++i)
        for (int j=0; j<n; ++j)
          if (result[i][j] > result[i][k] + result[k][j])
            result[i][j] = result[i][k] + result[k][j];

    return result;
  }
}
