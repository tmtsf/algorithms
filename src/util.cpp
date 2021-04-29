#include "util.hpp"
#include "graph.hpp"

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
      // get first line for number of points
      std::getline(in, line);
      std::istringstream first(line);
      first >> n;

      std::getline(in, line);
      while (std::getline(in, line))
      {
        std::istringstream iss(line);
        int from;
        int to;
        iss >> from >> to;
        edges.emplace_back(from, to);
      }
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
      // get first line for number of points
      std::getline(in, line);
      std::istringstream first(line);
      first >> n;

      std::getline(in, line);
      while (std::getline(in, line))
      {
        std::istringstream iss(line);
        int from;
        int to;
        double weight;
        iss >> from >> to >> weight;
        edges.emplace_back(std::make_tuple(from, to, weight));
      }
    }

    void validate_directed_graph(const graph_ptr_t& g)
    {
      auto p = dynamic_cast<cheetah::mixins::directed*>(g.get());
      if (!p)
      {
        std::cout << "Can only generate a shortest path tree for a directed graph!\n";
        exit(1);
      }
    }

    void validate_undirected_graph(const graph_ptr_t& g)
    {
      auto p = dynamic_cast<cheetah::mixins::undirected*>(g.get());
      if (!p)
      {
        std::cout << "Can only generate a minimum spanning tree for an undirected graph!\n";
        exit(1);
      }
    }
  }
}
