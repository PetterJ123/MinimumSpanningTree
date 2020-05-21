// @Author:             Petter Johansson
// @Date:               Thursday 22/5 - 2020

// @Description:        This is a program that takes a text-file containing nodes and their weights to then run kruskals algorithm and find the minimum spanning tree (MST). This software makes use of the standard library and the disjoint-set algorithm (or union find algorithm).

// @Input:              a path to a text-file containing nodes and their weights
// @Output:             a text-file of which nodes and edges are left in the MST

#include "Edge.h"
#include "DisjointSet.h"
#include "func.h"

struct compare
{   
    // compares and returns one of edge weights
    inline bool operator() (Edge const &a, Edge const &b)
    {
        return (a.weight > b.weight);
    }
};

int main(int argc, char *argv[])
{
    // takes input file path
    std::string filePath = "";
    if(argc < 2)
    {
        std::cout << "Missing arguments" << "\n";
        return -1;
    }
    filePath = argv[1];

    std::fstream fileStream;
    fileData fd;
    // extracts data from the input file
    fd = extractData(fd, filePath);

    // Maps and gives each node a unique 'id' number
    std::vector<Edge> edges;
    for(auto& c : fd.connections)
    {
        auto search = fd.nodeMap.find(std::get<0>(c));
        auto search2 = fd.nodeMap.find(std::get<1>(c));
        edges.push_back({search->second, search2->second, std::get<2>(c)});
    }
    
    // sorts edges to asending order with compare()
    std::sort(edges.begin(), edges.end(), compare());

    // run kruskals algorithm
    std::vector<Edge> st = kruskal(edges, fd.nodes.size());
    
    // find and map back nodes to their id
    fd = mapIntToStr(fd, st);

    // produce output-file Answer.txt
    outputKruskalsData(fileStream, fd);

    return 0;
}