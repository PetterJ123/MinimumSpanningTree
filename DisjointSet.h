#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#include <unordered_map>

class DisjointSet
{
    std::unordered_map<int, int> parent;

    public:
        void makeSet(int vertCount)
        {
            for(int i=0; i<vertCount; i++)
            {
                parent[i] = i;
            }
        }

        int Find(int k)
        {
            if(parent[k] == k)
            {
                return k;
            }

            return Find(parent[k]);
        }

        void Union(int a, int b)
        {
            int x = Find(a);
            int y = Find(b);

            parent[x] = y;
        }
};

#endif