#include "gtest/gtest.h"
#include "priority_queue.hpp"
#include "indexed_priority_queue.hpp"

namespace cheetah
{
  namespace test
  {
    TEST(test_priority_queue, Test)
    {
      std::vector<int> v = {1, 2, 3, 4, 5};
      cheetah::priority_queue<int> pq;
      for (int num : v)
      {
        pq.push(num);
        for (int nn : pq)
          std::cout << nn << "  ";

        std::cout << "\n";
      }

      std::cout << "\n";
      while (!pq.empty())
      {
        pq.pop();
        for (int nn : pq)
          std::cout << nn << "  ";

        std::cout << "\n";
      }
    }

    TEST(test_indexed_priority_queue, Test)
    {
      std::vector<std::string> v = {"it", "was", "the", "best", "of", "times", "it", "was", "the", "worst"};
      cheetah::indexed_priority_queue<std::string> pq;
      for (int i=0; i<v.size(); ++i)
      {
        pq.push(i, v[i]);
      }

      pq.remove(5);

      if (!pq.contains(5))
        pq.push(5, "times");

      if (pq.contains(2))
        pq.change(2, "a");

      if (pq.contains(10))
        std::cout << "This is impossible!\n";

      while (!pq.empty())
      {
        std::cout << pq.top() << "\n";
        pq.pop();
      }
    }
  }
}
