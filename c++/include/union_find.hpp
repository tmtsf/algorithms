#pragma once

#include "fwd_decl.hpp"

namespace cheetah
{
  struct union_find
  {
    virtual ~union_find(void) = default;
  public:
    virtual void join(int p, int q) = 0;
    virtual int find(int p) const = 0;
    virtual int count(void) const = 0;
  public:
    bool connected(int p, int q) const
    {
      return find(p) == find(q);
    }
  public:
    static cheetah::union_find_ptr_t make_quick_find(int n);
    static cheetah::union_find_ptr_t make_quick_union(int n);
    static cheetah::union_find_ptr_t make_weighted_quick_union(int n);
    static cheetah::union_find_ptr_t make_weighted_path_compressed_quick_union(int n);
  };
}
