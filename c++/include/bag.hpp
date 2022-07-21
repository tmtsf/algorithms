#pragma once

#include "container.hpp"

namespace cheetah
{
  template<typename T>
  struct bag
  {
    bag() : first(nullptr), N(0)
    { }
    ~bag()
    {
      while (first)
      {
        node<T>* curr = first;
        first = first->next;
        delete curr;
      }
    }
    void push(const T& elem)
    {
      node<T>* temp = new node<T>(elem, first);
      first = temp;
      ++N;
    }
    bool empty(void)
    {
      return N == 0;
    }
    int size(void)
    {
      return N;
    }
    virtual iterator<T> begin(void)
    {
      return iterator<T>(first);
    }
    virtual const iterator<T> begin(void) const
    {
      return iterator<T>(first);
    }
    iterator<T> end(void)
    {
      return iterator<T>{};
    }
    const iterator<T> end(void) const
    {
      return iterator<T>{};
    }
  private:
    node<T>* first;
    int N;
  };
}
