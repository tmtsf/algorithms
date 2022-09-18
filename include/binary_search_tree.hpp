#pragma once

#include "fwd_decl.hpp"

namespace cheetah
{
  template<typename Key, typename Value, typename Compare = std::less<Key>>
  struct binary_search_tree
  {
  private:
    struct node
    {
      node(const Key& key_,
           const Value& value_) :
        key(key_),
        value(value_),
        left(nullptr),
        right(nullptr)
      { }

      Key key;
      Value value;
      node* left;
      node* right;
    };
  public:
    binary_search_tree(void) :
      root(nullptr)
    { }
    binary_search_tree(const binary_search_tree& other) = delete;
    binary_search_tree& operator=(const binary_search_tree& other) = delete;
    ~binary_search_tree(void)
    {
      if (root)
        erase(root);
    }
  private:
    void erase(node* tn)
    {
      if (tn->left)
        erase(tn->left);
      if (tn->right)
        erase(tn->right);

      delete tn;
    }

  public:
    void inorder_print(void) const
    {
      inorder_print_helper(root);
    }
  private:
    void inorder_print_helper(node* tn) const
    {
      if (tn)
      {
        inorder_print_helper(tn->left);
        std::cout << tn->key << "   " << tn->value << "\n";
        inorder_print_helper(tn->right);
      }
    }

  public:
    void insert(const std::pair<Key, Value>& pair)
    {
      root = insert_helper(root, pair);
    }
  private:
    node* insert_helper(node* tn,
                        const std::pair<Key, Value>& pair)
    {
      if (!tn)
      {
        return new node(pair.first, pair.second);
      }

      if (comp(pair.first, tn->key))
      {
        tn->left = insert_helper(tn->left, pair);
      }
      else if (comp(tn->key, pair.first))
      {
        tn->right = insert_helper(tn->right, pair);
      }
      else
      {
        tn->value = pair.second;
      }

      return tn;
    }

  public:
    Value& operator[](const Key& key)
    {
      node* tn = get(root, key);
      if (!tn)
      {
        tn = insert_helper(root, {key, Value{}});
      }

      return tn->value;
    }
  private:
    node* get(node* tn, const Key& key)
    {
      if (!tn)
      {
        return nullptr;
      }

      if (comp(key, tn->key))
        return get(tn->left, key);
      else if (comp(tn->key, key))
        return get(tn->right, key);
      else
      {
        return tn;
      }
    }

  public:
    void erase(const Key& key)
    {
      root = erase(root, key);
    }
  private:
    void erase_min(void)
    {
      if (root)
        root = erase_min(root);
    }
    node* erase_min(node* tn)
    {
      if (!tn->left)
      {
        node* temp = tn->right;
        delete tn;
        return temp;
      }

      tn->left = erase_min(tn->left);
      return tn;
    }
    node* min(void) const
    {
      return min(root);
    }
    node* min(node* tn) const
    {
      if (!tn->left)
        return tn;

      return min(tn->left);
    }
    node* erase(node* tn, const Key& key)
    {
      if (!tn)
        return nullptr;

      if (comp(key, tn->key))
        tn->left = erase(tn->left, key);
      else if (comp(tn->key, key))
        tn->right = erase(tn->right, key);
      else
      {
        if (!tn->left)
        {
          node* temp = tn->right;
          delete tn;
          return temp;
        }

        if (!tn->right)
        {
          node* temp = tn->left;
          delete tn;
          return temp;
        }

        node* temp = tn;
        temp = min(tn->right);
        tn->key = temp->key;
        tn->value = temp->value;

        tn->right = erase_min(tn->right);
      }

      return tn;
    }
  private:
    Compare comp;
    node* root;
  };
}
