#include "gtest/gtest.h"
#include "heap_sort.hpp"

namespace cheetah
{
  namespace test
  {
    TEST(test_heap_sort, Sort)
    {
      std::vector<int> v = {3, 5, 1, -2, -7, 9, 4, 6, 1, -1};
      std::vector<int> c = v;

      cheetah::heap_sort(v);
      std::sort(c.begin(), c.end());
      assert(std::equal(v.cbegin(), v.cend(), c.cbegin()));

      v = {3, 5, 1, -2, -7, 9, 4, 6, 1, -1};
      c = v;

      cheetah::heap_sort(v, std::greater<int>());
      std::sort(c.begin(), c.end(), std::greater<int>());
      assert(std::equal(v.cbegin(), v.cend(), c.cbegin()));
    }
  }
}
