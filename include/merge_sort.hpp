#pragma once

#include "fwd_decl.hpp"

namespace cheetah
{
  namespace
  {
    template<typename T>
    void merge(std::vector<T>& v,
               std::size_t lo,
               std::size_t mid,
               std::size_t hi,
               std::vector<T>& aux)
    {
      for (size_t k=lo; k<hi; ++k)
        aux[k] = v[k];

      size_t i = lo;
      size_t j = mid;
      for (size_t k=lo; k<hi; ++k)
      {
        if (i == mid)
          v[k] = aux[j++];
        else if (j == hi)
          v[k] = aux[i++];
        else if (aux[j] < aux[i])
          v[k] = aux[j++];
        else
          v[k] = aux[i++];
      }
    }

    template<typename T>
    void sort(std::vector<T>& v,
              std::size_t lo,
              std::size_t hi,
              std::vector<T>& aux)
    {
      if (hi - lo <= 1)
        return;

      size_t mid = lo + (hi - lo) / 2;
      sort(v, lo, mid, aux);
      sort(v, mid, hi, aux);
      merge(v, lo, mid, hi, aux);
    }

    template<typename T, typename Comp>
    void merge(std::vector<T>& v,
               std::size_t lo,
               std::size_t mid,
               std::size_t hi,
               const Comp& comp,
               std::vector<T>& aux)
    {
      for (size_t k=lo; k<hi; ++k)
        aux[k] = v[k];

      size_t i = lo;
      size_t j = mid;
      for (size_t k=lo; k<hi; ++k)
      {
        if (i == mid)
          v[k] = aux[j++];
        else if (j == hi)
          v[k] = aux[i++];
        else if (comp(aux[j], aux[i]))
          v[k] = aux[j++];
        else
          v[k] = aux[i++];
      }
    }

    template<typename T, typename Comp>
    void sort(std::vector<T>& v,
              std::size_t lo,
              std::size_t hi,
              const Comp& comp,
              std::vector<T>& aux)
    {
      if (hi - lo <= 1)
        return;

      size_t mid = lo + (hi - lo) / 2;
      sort(v, lo, mid, comp, aux);
      sort(v, mid, hi, comp, aux);
      merge(v, lo, mid, hi, comp, aux);
    }
  }

  template<typename T>
  void merge_sort(std::vector<T>& v)
  {
    std::vector<T> aux(v);
    sort(v, 0, v.size(), aux);
  }

  template<typename T, typename Comp>
  void merge_sort(std::vector<T>& v, const Comp& comp)
  {
    std::vector<T> aux(v);
    sort(v, 0, v.size(), comp, aux);
  }
}
