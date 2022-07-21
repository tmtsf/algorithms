#include "gtest/gtest.h"
#include "bag.hpp"

namespace cheetah
{
  namespace test
  {
    TEST(test_bag, Modification)
    {
      cheetah::bag<int> s;

      std::vector<int> v = {1,2,3,4,5};
      for (int num : v)
        s.push(num);

      for (int num : s)
        std::cout << num << "\n";
      std::cout << "\n";

      EXPECT_EQ(s.size(), v.size());
      ASSERT_TRUE(!s.empty());
    }
  }
}
