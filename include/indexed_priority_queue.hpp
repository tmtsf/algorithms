#pragma once

#include "fwd_decl.hpp"

namespace cheetah
{
  template<typename T, typename Comp = std::less<T>>
  struct indexed_priority_queue
  {
  public:
    void push(int k, const T& item)
    {
      validate_index(k);
      if (contains(k))
      {
        throw("The index is already in the priority queue!");
        exit(1);
      }

      index.push_back(k);

      if (lookup.size() < k+1)
        lookup.resize(k+1, -1);

      lookup[k] = index.size() - 1;

      if (q.size() < k+1)
        q.resize(k+1, T());

      q[k] = item;

      swim(index.size() - 1);

      // for (const auto& i : q)
      //   std::cout << i << "  ";
      // std::cout << "\n";
      // for (const auto& i : index)
      //   std::cout << i << "  ";
      // std::cout << "\n";
      // for (const auto& i : lookup)
      //   std::cout << i << "  ";
      // std::cout << "\n";
    }
    void change(int k, const T& item)
    {
      validate_index(k);
      if (!contains(k))
      {
        throw("The index is not in the priority queue!");
        exit(1);
      }

      q[k] = item;
      swim(lookup[k]);
      sink(lookup[k]);
    }
    void pop(void)
    {
      swap(0, index.size() - 1);
      lookup[index.back()] = -1;
      index.pop_back();
      sink(0);
    }
    void remove(int k)
    {
      validate_index(k);
      if (!contains(k))
      {
        throw("The index is not in the priority queue!");
        exit(1);
      }
      int i = lookup[k];
      swap(i, index.size() - 1);
      lookup[index.back()] = -1;
      index.pop_back();
      swim(i);
      sink(i);
    }
    const T& top(void) const
    {
      return q[index[0]];
    }
    int size(void) const
    {
      return index.size();
    }
    bool empty(void) const
    {
      return index.empty();
    }
    bool contains(int i) const
    {
      validate_index(i);
      return i < lookup.size() && lookup[i] != -1;
    }
    typename std::vector<T>::const_iterator begin(void) const
    {
      return q.cbegin();
    }
    typename std::vector<T>::const_iterator end(void) const
    {
      return q.cend();
    }
    void print(void) const
    {
      for (const auto& i : q)
        std::cout << i << "  ";
      std::cout << "\n";
      for (const auto& i : index)
        std::cout << i << "  ";
      std::cout << "\n";
      for (const auto& i : lookup)
        std::cout << i << "  ";
      std::cout << "\n";
    }
  private:
    void swim(std::size_t k)
    {
      while (k > 0 && compare((k-1)/2, k))
      {
        swap((k-1)/2, k);
        k = (k-1)/2;
      }
    }
    void sink(std::size_t k)
    {
      std::size_t sz = index.size();
      while (2*k+1 < sz)
      {
        std::size_t j = 2*k + 1;
        if (j+1 < sz && compare(j, j+1))
          ++j;
        if (!compare(k, j))
          break;

        swap(k, j);
        k = j;
      }
    }
    void validate_index(int i) const
    {
      if (i < 0)
      {
        throw("Cannot accept a negative index");
        exit(1);
      }
    }
    bool compare(int i, int j) const
    {
      return comp(q[index[i]], q[index[j]]);
    }
    void swap(int i, int j)
    {
      std::swap(index[i], index[j]);
      lookup[index[i]] = i;
      lookup[index[j]] = j;
    }
  private:
    std::vector<T> q;

    // index[lookup[i]] = lookup[index[i]] = i
    std::vector<int> index;
    std::vector<int> lookup;
    Comp comp;
  };
}
