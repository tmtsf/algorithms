#include "gtest/gtest.h"
#include "binary_search_tree.hpp"

namespace cheetah
{
  namespace test
  {
    TEST(test_BST, Modification)
    {
      std::vector<int> v = {3, 5, 1, -2, -7, 9, 4, 6, 1, -1};

      cheetah::binary_search_tree<int, int> m;
      int count = 0;
      for (int num : v)
      {
        m.insert({num, count++});
        std::cout << m[num] << "\n";
        std::cout << "Printing tree with " << count << " elements:\n";
        m.inorder_print();
        std::cout << "\n\n";
      }

      std::cout << m[8] << "\n";
      m[8] = count++;
      std::cout << m[8] << "\n";

      for (int i=0; i<v.size()/2; ++i)
      {
        m.erase(v[i]);
        std::cout << "Printing tree with " << --count << " elements:\n";
        m.inorder_print();
        std::cout << "\n\n";
      }
    }
  }
}
