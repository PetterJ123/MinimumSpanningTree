#ifndef FUNC_H
#define FUNC_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <tuple>
#include "Edge.h"
#include "DisjointSet.h"

struct fileData
{
    std::vector<std::string> nodes;
    std::unordered_map<std::string, int> nodeMap;
    std::unordered_map<int, std::string> invertedNodeMap;
    std::vector<std::tuple<std::string, std::string, int>> connections;
};

std::vector<Edge> kruskal(std::vector<Edge> edges, int vertCount)
{
    // spanningtree result vector
    std::vector<Edge> spanningTree;

    DisjointSet disjointSet;
    disjointSet.makeSet(vertCount);

    while(spanningTree.size() != vertCount - 1)
    {
        Edge nextEdge = edges.back();
        edges.pop_back();

        int x = disjointSet.Find(nextEdge.source);
        int y = disjointSet.Find(nextEdge.destination);

        if(x!=y)
        {
            spanningTree.push_back(nextEdge);
            disjointSet.Union(x,y);
        }
    }
    return spanningTree;
}

fileData extractData(fileData fd, std::string fpath)
{
    std::stringstream ss;
    std::fstream fileStream;
    fileStream.open(fpath);
    std::string line, srcNode, dstNode;
    int weight, mapNum = 0;
    bool halfFile = false;

    while(std::getline(fileStream, line))
    {
        if(line.empty() && !halfFile)
        {
            halfFile = true;
        }
        else if(halfFile)
        {
            ss.str(line);
            ss >> srcNode >> dstNode >> weight;
            ss.clear();
            ss.seekg(0, std::ios::beg);
            fd.connections.push_back({srcNode, dstNode, weight});
        }
        else
        {
            fd.nodeMap[line] = mapNum;
            fd.invertedNodeMap[mapNum] = line;
            fd.nodes.push_back(line);
            mapNum++;
        }
    }
    
    return fd;
}

#endif