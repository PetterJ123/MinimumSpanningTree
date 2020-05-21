#ifndef FUNC_H
#define FUNC_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
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

// @param edges;     vector of edges extracted from input-file
// @param vertCount; the amout of verticies
// @return;         vector of edges in spanning tree
std::vector<Edge> kruskal(std::vector<Edge> edges, int vertCount)
{
    // spanningtree result vector
    std::vector<Edge> spanningTree;

    DisjointSet disjointSet;
    disjointSet.makeSet(vertCount);

    // pick an edge and make sure it doesn't make a cycle
    while(spanningTree.size() != vertCount - 1)
    {
        Edge nextEdge = edges.back();
        edges.pop_back();
        
        int setItemX = disjointSet.Find(nextEdge.source);
        int setItemY = disjointSet.Find(nextEdge.destination);

        // .. union if no cycle detected
        if(setItemX != setItemY)
        {
            spanningTree.push_back(nextEdge);
            disjointSet.Union(setItemX,setItemY);
        }
    }
    return spanningTree;
}

// @param fd;   struct instance containing data extracted and worked on by this program
// @param fpath;    string marking path to input file
// @return;     filedata object
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
            // extract edges and their connections
            ss.str(line);
            ss >> srcNode >> dstNode >> weight;
            ss.clear();
            ss.seekg(0, std::ios::beg);
            fd.connections.push_back({srcNode, dstNode, weight});
        }
        else
        {
            // extract nodes and insert into two maps
            fd.nodeMap[line] = mapNum;
            fd.invertedNodeMap[mapNum] = line;
            fd.nodes.push_back(line);
            mapNum++;
        }
    }
    
    return fd;
}

// @param fstream;  reference to filestream object
// @param fd;       struct instance containing data extracted and worked on by this program
// @return;         void
void outputKruskalsData(std::fstream& fstream, fileData fd)
{
    fstream.open("Answer.txt", std::ios::out | std::ios::trunc);

    int k=0, i=0;
    while(k != fd.nodes.size())
    {
        // if inputnodes is same as node after algorithm...
        if(fd.nodes[k] == fd.outputNodes[i])
        {
            // ...output to file 
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

    // output edges and their weights
    for(auto &a : fd.outputWeights)
    {
        fstream << std::get<0>(a) << "\t" << std::get<1>(a) << "\t" << std::get<2>(a) << "\n";
    }
}

// @param fd;   struct instance containing data extracted and worked on by this program
// @param spt;  edges that are in the spanning tree after kruskal's algorithm
// @return;     updated filedata object
fileData mapIntToStr(fileData fd, std::vector<Edge>& spt)
{
    int weightSum = 0;
    for(auto &s : spt)
    {
        auto search = fd.invertedNodeMap.find(s.source);
        auto search2 = fd.invertedNodeMap.find(s.destination);
        fd.outputWeights.push_back({search->second, search2->second, s.weight});
        weightSum += s.weight;
        fd.outputNodes.push_back(search->second);
        fd.outputNodes.push_back(search2->second);
    }
    std::cout << "Sum of MST: " << weightSum << "\n";
    return fd;
}

#endif