#include "util.hpp"
#include "graph.hpp"

namespace cheetah
{
  namespace util
  {
    namespace
    {
      std::vector<std::string> split(const std::string& str,
                                    const std::string& delim)
      {
        std::vector<std::string> tokens;
        std::size_t start = 0;
        std::size_t pos;
        while (true)
        {
          pos = str.find(delim, start);
          tokens.push_back(str.substr(start, pos-start));
          if (pos == std::string::npos)
          {
            break;
          }
          else
          {
            start = pos + delim.size();
          }
        }

        return tokens;
      }
    }

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

    void parse_unweighted_graph(const char* filename,
                                const std::string& delim,
                                std::vector<std::pair<int, int>>& edges,
                                std::unordered_map<std::string, int>& lookup,
                                std::vector<std::string>& symbols)
    {
      std::ifstream in(filename);
      if (!in.is_open())
      {
        std::cout << "File failed to open.\n";
        exit(1);
      }

      std::string line;
      while (std::getline(in, line))
      {
        std::vector<std::string> vertices = split(line, delim);
        for (const std::string& vertex : vertices)
        {
          if (!lookup.count(vertex))
            lookup[vertex] = lookup.size();
        }

        for (std::size_t i=1; i<vertices.size(); ++i)
          edges.emplace_back(lookup[vertices.front()], lookup[vertices[i]]);
      }

      symbols.resize(lookup.size());
      for (const auto& item : lookup)
        symbols[item.second] = item.first;
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

    void parse_weighted_graph(const char* filename,
                              const std::string& delim,
                              std::vector<weighted_edge>& edges,
                              std::unordered_map<std::string, int>& lookup,
                              std::vector<std::string>& symbols)
    {
      std::ifstream in(filename);
      if (!in.is_open())
      {
        std::cout << "File failed to open.\n";
        exit(1);
      }

      std::string line;
      while (std::getline(in, line))
      {
        std::vector<std::string> inputs = split(line, delim);
        assert(inputs.size() == 3);
        if (!lookup.count(inputs[0]))
          lookup[inputs[0]] = lookup.size();
        if (!lookup.count(inputs[1]))
          lookup[inputs[1]] = lookup.size();

        double weight = std::stod(inputs[2]);
        edges.emplace_back(std::make_tuple(lookup[inputs[0]], lookup[inputs[1]], weight));
      }

      symbols.resize(lookup.size());
      for (const auto& item : lookup)
        symbols[item.second] = item.first;
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
