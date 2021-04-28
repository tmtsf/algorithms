#pragma once

#include <memory>
#include <cassert>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <numeric>
#include <vector>
#include <functional>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <limits>
#include <optional>
#include <cfloat>

namespace cheetah
{
  struct graph;
  using graph_ptr_t = std::shared_ptr<graph>;

  struct union_find;
  using union_find_ptr_t = std::shared_ptr<union_find>;

  using weighted_edge = std::tuple<int, int, double>;

  using int_vec_t = std::vector<int>;
  using int_vec_coll_t = std::vector<int_vec_t>;
  using int_mat_t = std::vector<int_vec_t>;

  using dbl_vec_t = std::vector<double>;
  using dbl_mat_t = std::vector<dbl_vec_t>;

  using bool_vec_t = std::vector<bool>;
}
