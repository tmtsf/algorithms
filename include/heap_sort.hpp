#pragma once

#include "fwd_decl.hpp"

namespace cheetah
{
  namespace
  {
    template<typename T>
    void swim(std::vector<T>& v,
              std::size_t k)
    {
      while (k >= 0 && v[(k-1)/2] < v[k])
      {
        std::swap(v[(k-1)/2], v[k]);
        k = (k-1) / 2;
      }
    }

    template<typename T>
    void sink(std::vector<T>& v,
              std::size_t k,
              std::size_t N)
    {
      while (2*k + 1 < N)
      {
        std::size_t j = 2*k + 1;
        if (j < N - 1 && v[j] < v[j+1])
          ++j;
        if (!(v[k] < v[j]))
          break;

        std::swap(v[k], v[j]);
        k = j;
      }
    }

    template<typename T, typename Comp>
    void swim(std::vector<T>& v,
              std::size_t k,
              const Comp& comp)
    {
      while (k >= 0 && comp(v[(k-1)/2], v[k]))
      {
        std::swap(v[(k-1)/2], v[k]);
        k = (k-1) / 2;
      }
    }

    template<typename T, typename Comp>
    void sink(std::vector<T>& v,
              std::size_t k,
              std::size_t N,
              const Comp& comp)
    {
      while (2*k + 1 < N)
      {
        std::size_t j = 2*k + 1;
        if (j < N - 1 && comp(v[j], v[j+1]))
          ++j;
        if (!comp(v[k], v[j]))
          break;

        std::swap(v[k], v[j]);
        k = j;
      }
    }
  }

  template<typename T>
  void heap_sort(std::vector<T>& v)
  {
    std::size_t N = v.size();
    for (std::size_t k=0; k<=N/2; ++k)
      sink(v, N/2-k, N);

    while (N > 1)
    {
      std::swap(v[0], v[--N]);
      sink(v, 0, N);
    }
  }

  template<typename T, typename Comp>
  void heap_sort(std::vector<T>& v,
                 const Comp& comp)
  {
    std::size_t N = v.size();
    for (std::size_t k=0; k<=N/2; ++k)
      sink(v, N/2-k, N, comp);

    while (N > 1)
    {
      std::swap(v[0], v[--N]);
      sink(v, 0, N, comp);
    }
  }
}
