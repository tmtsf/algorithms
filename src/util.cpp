#include "util.hpp"

namespace cheetah
{
  namespace util
  {
    void parse_union_find_data(const char* filename,
                               std::vector<std::pair<int, int>>& edges,
                               int& n)
    {
      std::ifstream in(filename);
      if (!in.is_open())
      {
        std::cout << "File failed to open.\n";
        exit(1);
      }

      std::string line;
      // get first line for number of points
      std::getline(in, line);
      std::istringstream first(line);
      first >> n;

      // get connections
      while (std::getline(in, line))
      {
        std::istringstream iss(line);
        int from;
        int to;
        iss >> from >> to;
        edges.emplace_back(from, to);
      }
    }

    void parse_unweighted_graph(const char* filename,
                                std::vector<std::pair<int, int>>& edges,
                                int& n)
    {
      std::ifstream in(filename);
      if (!in.is_open())
      {
        std::cout << "File failed to open.\n";
        exit(1);
      }

      std::string line;
      std::unordered_set<int> s;
      while (std::getline(in, line))
      {
        std::istringstream iss(line);
        int from;
        int to;
        iss >> from >> to;
        s.insert(from);
        s.insert(to);
        edges.emplace_back(from, to);
      }

      n = s.size();
    }

    void parse_weighted_graph(const char* filename,
                              std::vector<weighted_edge>& edges,
                              int& n)
    {
      std::ifstream in(filename);
      if (!in.is_open())
      {
        std::cout << "File failed to open.\n";
        exit(1);
      }

      std::string line;
      std::unordered_set<int> s;
      while (std::getline(in, line))
      {
        std::istringstream iss(line);
        int from;
        int to;
        double weight;
        iss >> from >> to >> weight;
        s.insert(from);
        s.insert(to);
        edges.emplace_back(std::make_tuple(from, to, weight));
      }

      n = s.size();
    }
  }
}
