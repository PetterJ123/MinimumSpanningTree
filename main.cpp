#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include "Edge.h"
#include "DisjointSet.h"
#include "func.h"

struct compare
{
    inline bool operator() (Edge const &a, Edge const &b)
    {
        return (a.weight > b.weight);
    }
};

int main(int argc, char *argv[])
{
    std::string filePath = "";
    if(argc < 2)
    {
        std::cout << "Missing arguments" << "\n";
        return -1;
    }
    filePath = argv[1];

    std::fstream fileStream;
    fileData fd;
    fd = extractData(fd, filePath);

    std::vector<Edge> edges;
    for(auto& c : fd.connections)
    {
        auto search = fd.nodeMap.find(std::get<0>(c));
        auto search2 = fd.nodeMap.find(std::get<1>(c));
        edges.push_back({(int)search->second, (int)search2->second, (int)std::get<2>(c)});
    }
    
    std::sort(edges.begin(), edges.end(), compare());

    std::vector<Edge> st = kruskal(edges, fd.nodes.size());
    
    fd = mapIntToStr(fd, st);

    outputKruskalsData(fileStream, fd);

    return 0;
}