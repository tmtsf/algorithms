#pragma once

#include "fwd_decl.hpp"

namespace cheetah
{
  namespace
  {
    template<typename T>
    std::size_t partition(std::vector<T>& v,
                          std::size_t lo,
                          std::size_t hi)
    {
      std::size_t i = lo + 1;
      std::size_t j = hi - 1;
      T first = v[lo];
      while (true)
      {
        while (v[i] < first)
        {
          if (i == hi - 1)
            break;

          ++i;
        }

        while (first < v[j])
        {
          if (j == lo)
            break;

          --j;
        }

        if (i >= j)
          break;

        std::swap(v[i], v[j]);
      }

      std::swap(v[lo], v[j]);
      return j;
    }

    template<typename T>
    void sort(std::vector<T>& v,
              std::size_t lo,
              std::size_t hi)
    {
      if (hi - lo <= 1)
        return;

      std::size_t mid = partition(v, lo, hi);
      sort(v, lo, mid);
      sort(v, mid+1, hi);
    }

    template<typename T, typename Comp>
    std::size_t partition(std::vector<T>& v,
                          std::size_t lo,
                          std::size_t hi,
                          const Comp& comp)
    {
      std::size_t i = lo + 1;
      std::size_t j = hi - 1;
      T first = v[lo];
      while (true)
      {
        while (comp(v[i], first))
        {
          if (i == hi - 1)
            break;

          ++i;
        }

        while (comp(first, v[j]))
        {
          if (j == lo)
            break;

          --j;
        }

        if (i >= j)
          break;

        std::swap(v[i], v[j]);
      }

      std::swap(v[lo], v[j]);
      return j;
    }

    template<typename T, typename Comp>
    void sort(std::vector<T>& v,
              std::size_t lo,
              std::size_t hi,
              const Comp& comp)
    {
      if (hi - lo <= 1)
        return;

      std::size_t mid = partition(v, lo, hi, comp);
      sort(v, lo, mid, comp);
      sort(v, mid+1, hi, comp);
    }
  }

  template<typename T>
  void quick_sort(std::vector<T>& v)
  {
    sort(v, 0, v.size());
  }

  template<typename T, typename Comp>
  void quick_sort(std::vector<T>& v, const Comp& comp)
  {
    sort(v, 0, v.size(), comp);
  }
}
