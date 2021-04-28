#include "gtest/gtest.h"
#include "union_find.hpp"
#include "util.hpp"

namespace cheetah
{
  namespace test
  {
    TEST(test_quick_find, Tiny)
    {
      std::cout << "**********************************************\n";
      std::vector<std::pair<int, int>> edges;
      int n;
      cheetah::util::parse_unweighted_graph("data/tiny_union_find.txt", edges, n);

      cheetah::union_find_ptr_t uf = cheetah::union_find::make_quick_find(n);
      for (const auto& edge : edges)
        uf->join(edge.first, edge.second);

      std::cout << "There are " << uf->count() << " connected components.\n";
      std::cout << "**********************************************\n\n";
    }

    TEST(test_quick_find, Medium)
    {
      std::cout << "**********************************************\n";
      std::vector<std::pair<int, int>> edges;
      int n;
      cheetah::util::parse_unweighted_graph("data/medium_union_find.txt", edges, n);

      cheetah::union_find_ptr_t uf = cheetah::union_find::make_quick_find(n);
      for (const auto& edge : edges)
        uf->join(edge.first, edge.second);

      std::cout << "There are " << uf->count() << " connected components.\n";
      std::cout << "**********************************************\n\n";
    }

    TEST(test_quick_union, Tiny)
    {
      std::cout << "**********************************************\n";
      std::vector<std::pair<int, int>> edges;
      int n;
      cheetah::util::parse_unweighted_graph("data/tiny_union_find.txt", edges, n);

      cheetah::union_find_ptr_t uf = cheetah::union_find::make_quick_union(n);
      for (const auto& edge : edges)
        uf->join(edge.first, edge.second);

      std::cout << "There are " << uf->count() << " connected components.\n";
      std::cout << "**********************************************\n\n";
    }

    // TEST(test_quick_union, Medium)
    // {
    //   std::cout << "**********************************************\n";
    //   std::vector<std::pair<int, int>> edges;
    //   int n;
    //   cheetah::util::parse_unweighted_graph("data/medium_union_find.txt", edges, n);

    //   cheetah::union_find_ptr_t uf = cheetah::union_find::make_quick_union(n);
    //   for (const auto& edge : edges)
    //     uf->join(edge.first, edge.second);

    //   std::cout << "There are " << uf->count() << " connected components.\n";
    //   std::cout << "**********************************************\n\n";
    // }

    TEST(test_weighted_quick_union, Tiny)
    {
      std::cout << "**********************************************\n";
      std::vector<std::pair<int, int>> edges;
      int n;
      cheetah::util::parse_unweighted_graph("data/tiny_union_find.txt", edges, n);

      cheetah::union_find_ptr_t uf = cheetah::union_find::make_weighted_quick_union(n);
      for (const auto& edge : edges)
        uf->join(edge.first, edge.second);

      std::cout << "There are " << uf->count() << " connected components.\n";
      std::cout << "**********************************************\n\n";
    }

    TEST(test_weighted_quick_union, Medium)
    {
      std::cout << "**********************************************\n";
      std::vector<std::pair<int, int>> edges;
      int n;
      cheetah::util::parse_unweighted_graph("data/medium_union_find.txt", edges, n);

      cheetah::union_find_ptr_t uf = cheetah::union_find::make_weighted_quick_union(n);
      for (const auto& edge : edges)
        uf->join(edge.first, edge.second);

      std::cout << "There are " << uf->count() << " connected components.\n";
      std::cout << "**********************************************\n\n";
    }

    TEST(test_weighted_quick_union, Large)
    {
      std::cout << "**********************************************\n";
      std::vector<std::pair<int, int>> edges;
      int n;
      cheetah::util::parse_unweighted_graph("data/large_union_find.txt", edges, n);

      cheetah::union_find_ptr_t uf = cheetah::union_find::make_weighted_quick_union(n);
      for (const auto& edge : edges)
        uf->join(edge.first, edge.second);

      std::cout << "There are " << uf->count() << " connected components.\n";
      std::cout << "**********************************************\n\n";
    }
  }
}
