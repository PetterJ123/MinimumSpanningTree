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
    std::vector<std::string> nodes, outputNodes;
    std::unordered_map<std::string, int> nodeMap;
    std::unordered_map<int, std::string> invertedNodeMap;
    std::vector<std::tuple<std::string, std::string, int>> connections, outputWeights;
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

void outputKruskalsData(std::fstream& fstream, fileData fd)
{
    fstream.open("Answer.txt", std::ios::out | std::ios::trunc);
    int k=0, i=0;
    while(k!=fd.nodes.size())
    {
        if(fd.nodes[k] == fd.outputNodes[i])
        {
            // output to file here
            fstream << fd.outputNodes[i] << "\n";
            k++;
        }
        else if(i == fd.outputNodes.size())
        {
            i=0;
        }
        i++;
    }
    fstream << "\n";

    for(auto &a : fd.outputWeights)
    {
        fstream << std::get<0>(a) << "\t" << std::get<1>(a) << "\t" << std::get<2>(a) << "\n";
    }
}

fileData mapIntToStr(fileData fd, std::vector<Edge>& spt)
{
    for(auto &s : spt)
    {
        auto search = fd.invertedNodeMap.find(s.source);
        auto search2 = fd.invertedNodeMap.find(s.destination);
        fd.outputWeights.push_back({search->second, search2->second, s.weight});
        fd.outputNodes.push_back(search->second);
        fd.outputNodes.push_back(search2->second);
    }

    return fd;
}

#endif