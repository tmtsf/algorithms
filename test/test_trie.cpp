#include "gtest/gtest.h"
#include "trie.hpp"

namespace cheetah
{
  namespace test
  {
    // TEST(test_trie, Modification)
    // {
    //   std::vector<std::string> v = {"she", "sells", "sea", "shells", "by", "the", "sea", "shore"};

    //   cheetah::trie<int> m;
    //   int count = 0;
    //   for (const auto& str : v)
    //   {
    //     m.insert({str, count++});
    //   }

    //   std::cout << m["seashells"] << std::endl;
    //   m["seashells"] = count++;
    //   std::cout << m["seashells"] << std::endl << std::endl;

    //   for (const auto& str : v)
    //   {
    //     std::cout << str << ": " << m[str] << std::endl;
    //   }

    //   std::cout << std::endl;

    //   std::vector<std::string> keys_that_match = m.keys_that_match("s..");
    //   for (const auto& str : keys_that_match)
    //     std::cout << str << "\t";
    //   std::cout << std::endl << std::endl;

    //   std::cout << m.longest_prefix("she") << "\n";
    //   std::cout << m.longest_prefix("shell") << "\n";
    //   std::cout << m.longest_prefix("shellsort") << "\n";
    //   std::cout << m.longest_prefix("shelters") << "\n";
    //   std::cout << "\n";

    //   for (const auto& str : v)
    //   {
    //     m.erase(str);
    //   }

    //   std::vector<std::string> keys = m.keys();
    //   for (const auto& key : keys)
    //   {
    //     std::cout << key << ": " << m[key] << "\n";
    //   }

    //   std::cout << "\n";
    // }
  }
}
