#pragma once

#include "fwd_decl.hpp"

namespace cheetah
{
  namespace util
  {
    void parse_union_find_data(const char* filename,
                               std::vector<std::pair<int, int>>& edges,
                               int& n);

    void parse_unweighted_graph(const char* filename,
                                std::vector<std::pair<int, int>>& edges,
                                int& n);

    void parse_weighted_graph(const char* filename,
                              std::vector<weighted_edge>& edges,
                              int& n);

    template<typename T>
    struct greater;

    template<>
    struct greater<weighted_edge>
    {
      bool operator()(const weighted_edge& e1,
                      const weighted_edge& e2) const
      {
        return std::get<2>(e1) > std::get<2>(e2);
      }
    };
  }
}
