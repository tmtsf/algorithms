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
  }
}
