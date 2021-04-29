#pragma once

#include "fwd_decl.hpp"

namespace cheetah
{
  template<typename Value>
  struct trie
  {
  private:
    struct node
    {
      node(void)
      { }

      node(const Value& value_) : value(value_)
      { }

      std::optional<Value> value;

      static const int R = 256;
      node* children[R];
    };
  public:
    trie(void) : root(nullptr)
    { }
    trie(const trie& other) = delete;
    trie& operator=(const trie& other) = delete;
    ~trie(void)
    {
      if (root)
        erase(root);
    }
  private:
    void erase(node* tn)
    {
      for (node* child : tn->children)
      {
        if (child)
          erase(child);
      }

      delete tn;
    }

  public:
    void insert(const std::pair<std::string, Value>& pair)
    {
      root = insert_helper(root, pair, 0);
    }
  private:
    node* insert_helper(node* tn,
                        const std::pair<std::string, Value>& pair,
                        int d)
    {
      if (!tn)
        tn = new node();

      const std::string& key = pair.first;
      const Value& value = pair.second;

      if (key.size() == d)
      {
        tn->value = value;
        return tn;
      }

      const char& c = key[d];
      tn->children[c] = insert_helper(tn->children[c], pair, d+1);
      return tn;
    }

  public:
    Value& operator[](const std::string& key)
    {
      node* tn = get(root, key, 0);
      if (!tn)
      {
        tn = insert_helper(root, {key, Value{}}, 0);
      }

      return *(tn->value);
    }
  private:
    node* get(node* tn, const std::string& key, int d) const
    {
      if (!tn)
      {
        return nullptr;
      }

      if (key.size() == d)
        return tn;

      const char& c = key[d];
      return get(tn->children[c], key, d+1);
    }

  public:
    std::vector<std::string> keys(void) const
    {
      return keys_with_prefix("");
    }
    std::vector<std::string> keys_with_prefix(const std::string& prefix) const
    {
      std::vector<std::string> v;
      collect(get(root, prefix, 0), prefix, v);
      return v;
    }
  private:
    void collect(node* tn,
                 const std::string& prefix,
                 std::vector<std::string>& v) const
    {
      if (tn->value)
      {
        v.push_back(prefix);
      }
      for (int i=0; i<node::R; ++i)
      {
        if (tn->children[i])
        {
          char c = i;
          collect(tn->children[i], prefix+c, v);
        }
      }
    }

  public:
    std::vector<std::string> keys_that_match(const std::string& pattern) const
    {
      std::vector<std::string> v;
      collect(root, "", pattern, v);
      return v;
    }
  private:
    void collect(node* tn,
                 const std::string& prefix,
                 const std::string& pattern,
                 std::vector<std::string>& v) const
  {
    if (!tn)
      return;

    if (prefix.size() == pattern.size())
    {
      if (tn->value)
      {
        v.push_back(prefix);
      }
      else
      {
        return;
      }
    }

    const char& c = pattern[prefix.size()];
    for (int i=0; i<node::R; ++i)
    {
      char next = i;
      if (c == '.' || c == next)
        collect(tn->children[i], prefix+next, pattern, v);
    }
  }

  public:
    std::string longest_prefix(const std::string& s) const
    {
      int len;
      search(root, s, 0, len);
      return s.substr(0, len);
    }
  private:
    void search(node* tn,
                const std::string& s,
                int d,
                int& len) const
    {
      if (!tn)
        return;

      if (tn->value)
        len = d;

      if (s.size() == d)
        return;

      const char& c = s[d];
      search(tn->children[c], s, d+1, len);
    }

  public:
    void erase(const std::string& key)
    {
      root = erase(root, key, 0);
    }
  private:
    node* erase(node* tn, const std::string& key, int d)
    {
      if (!tn)
        return nullptr;

      if (key.size() == d)
      {
        tn->value = std::nullopt;
      }
      else
      {
        const char& c = key[d];
        tn->children[c] = erase(tn->children[c], key, d+1);
      }

      if (tn->value)
        return tn;

      for (int i=0; i<node::R; ++i)
      {
        if (tn->children[i])
          return tn;
      }

      delete tn;
      return nullptr;
    }
  private:
    node* root;
  };
}
