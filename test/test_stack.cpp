#include "gtest/gtest.h"
#include "stack.hpp"

namespace cheetah
{
  namespace test
  {
    TEST(test_stack, Modification)
    {
      cheetah::stack<int> s;

      std::vector<int> v = {1,2,3,4,5};
      for (int num : v)
        s.push(num);

      for (int num : s)
        std::cout << num << "\n";
      std::cout << "\n";

      while (!s.empty())
      {
        std::cout << s.top() << "  " << s.size() << "\n";
        s.pop();
      }

      std::cout << "\n";

      EXPECT_EQ(s.size(), 0);
      ASSERT_TRUE(s.empty());
    }
  }
}
