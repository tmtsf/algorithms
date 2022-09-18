#include "gtest/gtest.h"
#include "queue.hpp"

namespace cheetah
{
  namespace test
  {
    TEST(test_queue, Modification)
    {
      cheetah::queue<int> s;

      std::vector<int> v = {1,2,3,4,5};
      for (int num : v)
        s.push(num);

      for (int num : s)
        std::cout << num << "\n";
      std::cout << "\n";

      while (!s.empty())
      {
        std::cout << s.front() << "  " << s.size() << "\n";
        s.pop();
      }

      std::cout << "\n";

      EXPECT_EQ(s.size(), 0);
      ASSERT_TRUE(s.empty());
    }
  }
}
