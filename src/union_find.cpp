#include "union_find.hpp"

namespace cheetah
{
  namespace
  {
    struct quick_find_union_find : public union_find
    {
      quick_find_union_find(int n_) :
        n(n_)
      {
        id.resize(n);
        std::iota(id.begin(),
                  id.end(),
                  0);
      }
    public:
      virtual void join(int p, int q)
      {
        int p_id = find(p);
        int q_id = find(q);

        if (p_id == q_id)
          return;

        for (std::size_t i=0; i<id.size(); ++i)
        {
          if (id[i] == p_id)
            id[i] = q_id;
        }

        --n;
      }
      virtual int find(int p) const
      {
        return id[p];
      }
      virtual int count(void) const
      {
        return n;
      }
    private:
      int n;
      std::vector<int> id;
    };

    struct quick_union_union_find : public union_find
    {
      quick_union_union_find(int n_) :
        n(n_)
      {
        id.resize(n);
        std::iota(id.begin(),
                  id.end(),
                  0);
      }
    public:
      virtual void join(int p, int q)
      {
        int p_id = find(p);
        int q_id = find(q);

        if (p_id == q_id)
          return;

        id[p_id] = q_id;
        --n;
      }
      virtual int find(int p) const
      {
        while (id[p] != p)
          p = id[p];

        return p;
      }
      virtual int count(void) const
      {
        return n;
      }
    private:
      int n;
      std::vector<int> id;
    };

    struct weighted_quick_union_union_find : public union_find
    {
      weighted_quick_union_union_find(int n_) :
        n(n_)
      {
        id.resize(n);
        std::iota(id.begin(),
                  id.end(),
                  0);

        size.resize(n, 1);
      }
    public:
      virtual void join(int p, int q)
      {
        int p_id = find(p);
        int q_id = find(q);

        if (p_id == q_id)
          return;

      if (size[p_id] < size[q_id])
      {
        id[p_id] = q_id;
        size[q_id] += size[p_id];
      }
      else
      {
        id[q_id] = p_id;
        size[p_id] += size[q_id];
      }

        --n;
      }
      virtual int find(int p) const
      {
        while (id[p] != p)
          p = id[p];

        return p;
      }
      virtual int count(void) const
      {
        return n;
      }
    private:
      int n;
      std::vector<int> id;
      std::vector<int> size;
    };
  }

  cheetah::union_find_ptr_t union_find::make_quick_find(int n)
  {
    return std::make_shared<quick_find_union_find>(n);
  }

  cheetah::union_find_ptr_t union_find::make_quick_union(int n)
  {
    return std::make_shared<quick_union_union_find>(n);
  }

  cheetah::union_find_ptr_t union_find::make_weighted_quick_union(int n)
  {
    return std::make_shared<weighted_quick_union_union_find>(n);
  }
}
