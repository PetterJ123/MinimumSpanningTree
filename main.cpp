// @Author:             Petter Johansson
// @Date:               Sunday 9/8 - 2020

// @Description:        This is a program that takes a text-file containing nodes and their weights to then run kruskals algorithm and find the minimum spanning tree (MST). This software makes use of the standard library and the disjoint-set algorithm (or union find algorithm).
// Example:             A
//                      B
//                      C
//                      D

//                      A   B   3
//                      B   C   3
//                      C   D   1

// @Input:              a path to a text-file containing nodes and their weights
// @Output:             a text-file of which nodes and edges are left in the MST

#include "func.h"
#include <chrono>
#include <sys/stat.h>
#include <sys/stat.h>

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
    auto totStart = std::chrono::steady_clock::now();
    struct stat info;

    // checks if correct number of arguments are passed
    if(argc < 2)
    {
        std::cout << "Missing arguments" << "\n";
        return -1;
    }
    else if (argc > 2)
    {
        std::cout << "Can only handle two arguments\n";
        return -1;
    }

    // Check to see if path exists
    if(stat(argv[1], &info) != 0)
    {
        std::cout << "Path doesn't exist\n";
        return -1;
    }

    std::string filePath = argv[1];
        
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

    auto mstStart = std::chrono::steady_clock::now();
    
    // run kruskals algorithm
    std::vector<Edge> st = kruskal(edges, fd.nodes.size());

    auto mstStop = std::chrono::steady_clock::now();

    // find and map back nodes to their id
    fd = mapIntToStr(fd, st);

    // produce output-file Answer.txt
    outputKruskalsData(fileStream, fd);
    
    // Stop clocks and print results
    auto totStop = std::chrono::steady_clock::now();
    std::chrono::duration<double> mstSec = mstStop - mstStart;
    std::chrono::duration<double> tot = totStop - totStart;
    
    std::cout << "Kruskals took: " << mstSec.count() << " seconds\n"
                << "Total runtime: " << tot.count() << " seconds\n";

    return 0;
}