#include <iostream> // std::cout
#include <utility>  // std::pair
#include <fstream>  // std::ifstream
#include <string> // std::string
#include <vector>   // std::vector std::vector::iterator

// Author: Petter Johansson

class Node{
    public:
        std::string name;
};

class Edge {
    public:
        Node *entrypoints[2];
        int weight;
};

class Graph {
    public:
        Edge *edges;
        Node *nodes;
};

int main(int argc, char *argv[]){
    // Take in test data file path
    std::string file_path;
    if(argc < 2)
	{
		std::cout << "Missing arguments" << std::endl;
		return -1;
	}else{
        file_path = argv[1];
    }
    std::string data;

    // open file
    std::ifstream read_file_stream;
    read_file_stream.open(file_path, std::ios::in);

    // read nodes until space is found
    std::string line = "";
    std::vector<std::string> nodes;
    std::vector<std::string>::iterator it;
    std::vector<std::string> connections_n_weight;
    bool run_connections = false;

    while(std::getline(read_file_stream, line)){
        if(!line.empty() && run_connections != true){
            nodes.push_back(line);
        }
        else if(line.empty()){
            run_connections = true;
            std::cout << "run_connections now true\n";
        }
        else if(run_connections){
            connections_n_weight.push_back(line);
        }
    }

    for(it=nodes.begin(); it!=nodes.end(); ++it){
        std::cout << *it << "\n";
    }
    for(it=connections_n_weight.begin(); it!=connections_n_weight.end(); ++it){
        std::cout << *it << "\n";
    }

    return 0;
}

    //TODO: struct/class of a node; character, connections