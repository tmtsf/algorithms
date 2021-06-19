#pragma once

#include "container.hpp"

namespace cheetah
{
  template<typename T>
  struct stack
  {
    stack() : first(nullptr), N(0)
    { }
    ~stack()
    {
      while (!empty())
        pop();
    }
    void push(const T& elem)
    {
      node<T>* temp = new node<T>(elem, first);
      first = temp;
      ++N;
    }
    T& top(void)
    {
      return first->item;
    }
    const T& top(void) const
    {
      return first->item;
    }
    bool empty(void)
    {
      return N == 0;
    }
    void pop(void)
    {
      node<T>* temp = first;
      first = first->next;
      --N;
      delete temp;
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
