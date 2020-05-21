#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <tuple>

class Edge
{
    public:
        int source, destination, weight;
};

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

std::vector<Edge> kruskal(std::vector<Edge> edges, int vertCount)
{
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
    std::stringstream ss;
    fileStream.open(filePath);

    typedef std::vector<std::tuple<std::string, std::string, int>> tupleVector;
    typedef std::tuple<int, int, int> intTuple;
    int weight, mapNum = 0;
    bool connectionsBit;
    std::string line, srcNode, dstNode;
    std::unordered_map<std::string, int> nodeMap;
    std::unordered_map<int, std::string> nodeNrMap;
    std::vector<std::tuple<std::string, int>> nodeTuple;
    std::vector<std::string> nodes;
    tupleVector connections;
    
    while(std::getline(fileStream, line))
    {
        if(line.empty() && !connectionsBit)
        {
            connectionsBit = true;
        }
        else if(connectionsBit)
        {
            ss.str(line);
            ss >> srcNode >> dstNode >> weight;
            ss.clear();
            ss.seekg(0, std::ios::beg);
            connections.push_back({srcNode, dstNode, weight});
        }
        else
        {
            nodeMap[line] = mapNum;
            nodeNrMap[mapNum] = line;
            nodes.push_back(line);
            mapNum++;
        }
    }
    // find and replace each character in connections with corresponding character value in nodemap

    std::vector<Edge> edges;
    // std::cout << "==== CONNECTIONS =====\n";
    for(auto& c : connections)
    {
        auto search = nodeMap.find(std::get<0>(c));
        auto search2 = nodeMap.find(std::get<1>(c));
        edges.push_back({(int)search->second, (int)search2->second, (int)std::get<2>(c)});
    }
    
    std::sort(edges.begin(), edges.end(), compare());

    std::vector<Edge> st = kruskal(edges, nodes.size());
    
    std::vector<std::tuple<std::string, std::string, int>> res;
    std::vector<std::string> graphNodes;
    
    for(auto &s : st)
    {
        auto search = nodeNrMap.find(s.source);
        auto search2 = nodeNrMap.find(s.destination);
        // std::cout << search->second << " : " << search2->second << " : " << s.weight << "\n";
        res.push_back({search->second, search2->second, s.weight});
        graphNodes.push_back(search->second);
        graphNodes.push_back(search2->second);
    }

    // int i=0, j=0;
    // std::vector<std::string>::iterator it;
    // for(int k=0; k<nodes.size();)
    // {
    //     if(graphNodes[j] == nodes[k])
    //     {
    //         std::cout << graphNodes[j] << " = " << nodes[k] << "\n";
    //         k++;
    //     }
    // }
    int k=0, i=0;
    std::vector<std::string> outputNodes;
    while(k!=nodes.size())
    {
        if(nodes[k] == graphNodes[i])
        {
            // std::cout << nodes[k] << " = " << graphNodes[i] << "\n";
            outputNodes.push_back(graphNodes[i]);
            k++;
        }
        else if(i == graphNodes.size())
        {
            i=0;
        }
        i++;
    }
    std::cout << "======NODES=====\n";
    std::vector<std::string>::iterator it;
    for(it=outputNodes.begin(); it!=outputNodes.end(); it++)
    {
        std::cout << *it << "\n";
    }

    std::cout << "\n========CONNECTIONS AND WEIGHT=========\n";
    for(auto &a : res)
    {
        std::cout << std::get<0>(a) << "\t" << std::get<1>(a) << "\t" << std::get<2>(a) << "\n";
    }

    // std::vector<std::string>::iterator it;
    // for(it=nodeVec.begin(); it!=nodeVec.end(); it++){
    //     std::cout << *it << "\n";
    // }
    // auto it = std::find_if(nodeTuple.begin(), nodeTuple.end(), [](const std::tuple<std::string, int>& t) { return std::get<0>(t) == "f"; } );
    // if(it != nodeTuple.end())
    // {
    //     std::cout << "found\n";
    // }
    // else
    // {
    //     std::cout << "dont exist\n";
    // }
    // map back to characters
    

    // output to file

    return 0;
}

// nodeMap.at()
// std::cout << std::get<0>(tv) << " : " << std::get<1>(tv) << " : " << std::get<2>(tv) << "\n";
// std::get<0>(tv) = x.first;
// std::cout << x.first << " : " << x.second << "\n";

// while(i<nodeMap.size()){
//     // std::cout << nodeMap.at(nodes[i]) << " ";
//     i++;
// }
// for(const auto &n : nodeMap){
//     std::cout << "key: " << n.first << " val: " << n.second << "\n";
// }

// for(auto& g:conn){
//         std::cout << std::get<0>(g) << " " << std::get<1>(g) << " " << std::get<2>(g) << "\n";
//     }

// std::cout << "===== NODES =====\n";
    // std::vector<std::string>::iterator it;
    // for(it=nodes.begin(); it!= nodes.end(); it++){
    //     std::cout << *it << "\n";
    // }

    // std::cout << "======= nodemap ======\n";
    // // nodemap
    // for(auto &nm : nodeMap){
    //     std::cout << nm.first << " : " << nm.second << "\n";
    // }
    
    // auto search = nodeMap.find("A");
    // if(search != nodeMap.end()){
    //     std::cout << search->first << " " << search->second << "\n";
    // }else { std::cout << "nope\n"; }