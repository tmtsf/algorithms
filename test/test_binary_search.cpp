#include "gtest/gtest.h"
#include "heap_sort.hpp"
#include "binary_search.hpp"

namespace cheetah
{
  namespace test
  {
    TEST(test_binary_search, BinarySearch)
    {
      std::vector<int> v = {3, 5, 1, -2, -7, 9, 4, 6, 1, -1};
      cheetah::heap_sort(v);
      assert(cheetah::is_sorted(v));

      int target = -1;

      std::size_t loc = cheetah::lower_bound(v, target);
      auto i = std::lower_bound(v.cbegin(),
                                v.cend(),
                                target)
            - v.cbegin();
      assert(loc == i);

      loc = cheetah::upper_bound(v, target);
      i = std::upper_bound(v.cbegin(),
                          v.cend(),
                          target)
            - v.cbegin();
      assert(loc == i);

      loc = cheetah::binary_search(v, target);
      i = std::find(v.cbegin(),
                    v.cend(),
                    target)
        - v.cbegin();
      assert(loc == i);

      v = {3, 5, 1, -2, -7, 9, 4, 6, 1, -1};
      cheetah::heap_sort(v, std::greater<int>());
      assert(!cheetah::is_sorted(v));
      assert(cheetah::is_sorted(v, std::greater<int>()));

      target = 4;

      loc = cheetah::lower_bound(v, target, std::greater<int>());
      i = std::lower_bound(v.cbegin(),
                          v.cend(),
                          target,
                          std::greater<int>())
            - v.cbegin();
      assert(loc == i);

      loc = cheetah::upper_bound(v, target, std::greater<int>());
      i = std::upper_bound(v.cbegin(),
                          v.cend(),
                          target,
                          std::greater<int>())
            - v.cbegin();
      assert(loc == i);

      loc = cheetah::binary_search(v, target, std::greater<int>());
      i = std::find(v.cbegin(),
                    v.cend(),
                    target)
        - v.cbegin();
      assert(loc == i);
    }
  }
}
