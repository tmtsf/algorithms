#pragma once

#include "fwd_decl.hpp"

namespace cheetah
{
  template<typename T>
  struct node
  {
    node(void) :
      item(T()),
      next(nullptr)
    { }

    node(const T& item_,
         node<T>* next_) :
      item(item_),
      next(next_)
    { }

    T item;
    node<T>* next;
  };

  template<typename T>
  struct iterator
  {
    iterator(void) : ptr(nullptr)
    { }
    iterator(node<T>* ptr_) :
      ptr(ptr_)
    { }
    iterator& operator++(void)
    {
      ptr = ptr->next;
      return *this;
    }
    iterator operator++(int)
    {
      iterator temp = *this;
      ptr = ptr->next;
      return temp;
    }
    bool operator!=(const iterator& other)
    {
      return ptr != other.ptr;
    }
    const T& operator*(void) const
    {
      return ptr->item;
    }
    T& operator*(void)
    {
      return ptr->item;
    }
  private:
    node<T>* ptr;
  };
}
