#pragma once

#include "fwd_decl.hpp"

namespace cheetah
{
  template<typename T>
  std::size_t lower_bound(const std::vector<T>& v,
                          const T& target,
                          std::size_t lo,
                          std::size_t hi)
  {
    while (lo < hi)
    {
      std::size_t mid = lo + (hi - lo) / 2;
      if (v[mid] < target)
        lo = mid + 1;
      else
        hi = mid;
    }

    return lo;
  }

  template<typename T, typename Comp>
  std::size_t lower_bound(const std::vector<T>& v,
                          const T& target,
                          std::size_t lo,
                          std::size_t hi,
                          const Comp& comp)
  {
    while (lo < hi)
    {
      std::size_t mid = lo + (hi - lo) / 2;
      if (comp(v[mid], target))
        lo = mid + 1;
      else
        hi = mid;
    }

    return lo;
  }

  template<typename T>
  std::size_t upper_bound(const std::vector<T>& v,
                          const T& target,
                          std::size_t lo,
                          std::size_t hi)
  {
    while (lo < hi)
    {
      std::size_t mid = lo + (hi - lo) / 2;
      if (v[mid] <= target)
        lo = mid + 1;
      else
        hi = mid;
    }

    return lo;
  }

  template<typename T, typename Comp>
  std::size_t upper_bound(const std::vector<T>& v,
                          const T& target,
                          std::size_t lo,
                          std::size_t hi,
                          const Comp& comp)
  {
    while (lo < hi)
    {
      std::size_t mid = lo + (hi - lo) / 2;
      if (!comp(target, v[mid]))
        lo = mid + 1;
      else
        hi = mid;
    }

    return lo;
  }

  template<typename T>
  std::size_t lower_bound(const std::vector<T>& v,
                          const T& target)
  {
    return lower_bound(v, target, 0, v.size());
  }

  template<typename T, typename Comp>
  std::size_t lower_bound(const std::vector<T>& v,
                          const T& target,
                          const Comp& comp)
  {
    return lower_bound(v, target, 0, v.size(), comp);
  }

  template<typename T>
  std::size_t upper_bound(const std::vector<T>& v,
                          const T& target)
  {
    return upper_bound(v, target, 0, v.size());
  }

  template<typename T, typename Comp>
  std::size_t upper_bound(const std::vector<T>& v,
                          const T& target,
                          const Comp& comp)
  {
    return upper_bound(v, target, 0, v.size(), comp);
  }

  template<typename T>
  bool is_sorted(const std::vector<T>& v)
  {
    for (std::size_t i=0; i<v.size()-1; ++i)
    {
      if (v[i+1] < v[i])
        return false;
    }

    return true;
  }

  template<typename T, typename Comp>
  bool is_sorted(const std::vector<T>& v,
                 const Comp& comp)
  {
    for (std::size_t i=0; i<v.size()-1; ++i)
    {
      if (comp(v[i+1], v[i]))
        return false;
    }

    return true;
  }

  template<typename T>
  std::size_t binary_search(const std::vector<T>& v,
                            const T& target)
  {
    std::size_t loc = lower_bound(v, target);
    if (!(target < v[loc]))
      return loc;

    return v.size();
  }

  template<typename T, typename Comp>
  std::size_t binary_search(const std::vector<T>& v,
                            const T& target,
                            const Comp& comp)
  {
    std::size_t loc = lower_bound(v, target, comp);
    if (!comp(target, v[loc]))
      return loc;

    return v.size();
  }
}
