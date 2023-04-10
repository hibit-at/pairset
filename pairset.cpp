#include <map>
#include <set>
#include <iostream>

struct pairset
{
    std::set<std::pair<int, int>> data;
    std::map<int, int> count;
    int size;

    pairset()
    {
        data.insert({INT_MIN, INT_MIN});
        data.insert({INT_MAX, INT_MAX});
        size = 0;
    }

    bool contains(int x)
    {
        auto itr = prev(data.lower_bound({x + 1, x + 1}));
        auto [L, R] = *itr;
        return L <= x && x <= R;
    }

    bool insert(int x)
    {
        count[x]++;
        auto next_itr = data.lower_bound({x + 1, x + 1});
        auto itr = prev(next_itr);
        auto [L, R] = *itr;
        auto [next_L, next_R] = *next_itr;
        if (L <= x && x <= R)
        {
            size++;
            return false;
        }
        if (R == x - 1)
        {
            if (next_L == x + 1)
            {
                data.erase(itr);
                data.erase(next_itr);
                data.insert({L, next_R});
            }
            else
            {
                data.erase(itr);
                data.insert({L, x});
            }
        }
        else
        {
            if (next_L == x + 1)
            {
                data.erase(next_itr);
                data.insert({x, next_R});
            }
            else
            {
                data.insert({x, x});
            }
        }
        size++;
        return true;
    }

    bool remove(int x)
    {
        if (count[x] == 0)
        {
            return false;
        }
        count[x]--;
        if (count[x])
        {
            size--;
            return false;
        }
        auto next_itr = data.lower_bound({x + 1, x + 1});
        auto itr = prev(next_itr);
        auto [L, R] = *itr;
        auto [next_L, next_R] = *next_itr;
        if (x < L || R < x)
        {
            return false;
        }
        if (L == R)
        {
            data.erase(itr);
        }
        else if (x == L)
        {
            data.erase(itr);
            data.insert({x + 1, R});
        }
        else if (x == R)
        {
            data.erase(itr);
            data.insert({L, x - 1});
        }
        else
        {
            data.erase(itr);
            data.insert({L, x - 1});
            data.insert({x + 1, R});
        }
        size--;
        return true;
    }

    int mex(int x = 0)
    {
        auto [L, R] = *prev(data.lower_bound({x + 1, x + 1}));
        if (L <= x && x <= R)
        {
            return R + 1;
        }
        else
        {
            return x;
        }
    }

    int min()
    {
        auto itr = *data.lower_bound({INT_MIN + 1, INT_MIN + 1});
        return itr.first;
    }

    int max()
    {
        auto itr = *prev(data.lower_bound({INT_MAX, INT_MAX}));
        return itr.second;
    }
};

int main()
{
    std::cout << "compile check" << std::endl;
    return 0;
}