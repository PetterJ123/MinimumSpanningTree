#include <iostream> // std::cout
#include <fstream>  // std::ifstream
#include <string> // std::string
#include <vector>   // std::vector std::vector::iterator
#include <sstream>	// std::stringstream
#include <tuple>	// std::tuple

// Author: Petter Johansson

int main(int argc, char *argv[]){
	
	// Take in test data file path
	std::string file_path;
	if(argc < 2)
	{
		std::cout << "Missing arguments" << std::endl;
		return -1;
	}
	else
	{
		file_path = argv[1];
	}
	typedef std::tuple<std::string, std::string, int> conn_tuple;
	std::ifstream fs;
	fs.open(file_path, std::ios::in);

	std::string line = "", node1, node2, data;
	std::vector<std::string> nodes;
	std::vector<conn_tuple> conn_list;
	conn_tuple vert_weight;
	std::stringstream ss;
	int weight;
	bool run_connections = false;

	// read file contents and push back into vector
	while(std::getline(fs, line))
	{
		if(line.empty() && !run_connections)
		{
			run_connections = true;
		}
		else if(run_connections)
		{
			// add current line to string stream
			ss.str(line);
			// extract two nodes and weight
			ss >> node1 >> node2 >> weight;
			std::cout << "node1: " << node1 << 
						"\nnode2: " << node2 <<
						"\nweight: " << weight << 
						"\n";
			ss.clear();
			ss.seekg(0, std::ios::beg);
			// push back/add into pair-obj connections_weight
			std::get<0>(vert_weight) = node1;
			std::get<1>(vert_weight) = node2;
			std::get<2>(vert_weight) = weight;
			conn_list.push_back(vert_weight);
		}
	}

	for(const auto& i : conn_list){
		std::cout << std::get<0>(i) << " " << std::get<1>(i) << " " << std::get<2>(i) << "\n";
	}
	
	return 0;
}