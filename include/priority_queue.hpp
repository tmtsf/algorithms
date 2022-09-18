#pragma once

#include "fwd_decl.hpp"

namespace cheetah
{
  template<typename T, typename Comp = std::less<T>>
  struct priority_queue
  {
  public:
    void push(const T& item)
    {
      q.push_back(item);
      swim(q.size() - 1);
    }
    void pop(void)
    {
      std::swap(q.front(), q.back());
      q.pop_back();
      sink(0);
    }
    const T& top(void) const
    {
      return q.front();
    }
    int size(void) const
    {
      return q.size();
    }
    bool empty(void) const
    {
      return q.empty();
    }
    typename std::vector<T>::const_iterator begin(void) const
    {
      return q.cbegin();
    }
    typename std::vector<T>::const_iterator end(void) const
    {
      return q.cend();
    }
  private:
    void swim(std::size_t k)
    {
      while (k > 0 && comp(q[(k-1)/2], q[k]))
      {
        std::swap(q[(k-1)/2], q[k]);
        k = (k-1)/2;
      }
    }
    void sink(std::size_t k)
    {
      std::size_t sz = q.size();
      while (2*k+1 < sz)
      {
        std::size_t j = 2*k + 1;
        if (j+1 < sz && comp(q[j], q[j+1]))
          ++j;
        if (!comp(q[k], q[j]))
          break;

        std::swap(q[k], q[j]);
        k = j;
      }
    }
  private:
    std::vector<T> q;
    Comp comp;
  };
}
