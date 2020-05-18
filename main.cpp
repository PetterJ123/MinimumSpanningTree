#include <iostream> // std::cout
#include <utility>  // std::pair
#include <fstream>  // std::ifstream
#include <string> // std::string
#include <vector>   // std::vector std::vector::iterator
#include <sstream>

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
	std::string data;

	// open file
	std::ifstream fs;
	fs.open(file_path, std::ios::in);
	
	std::string line = "";
	std::vector<std::string> nodes;
	std::pair<std::pair<std::string, std::string>, int> connections_weight;
	std::stringstream ss;
	std::string node1, node2;
	int weight;
	bool run_connections = false;

	// read file contents and push back into vector
	while(std::getline(fs, line))
	{
		// file_content.push_back(line);
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
			
		}
		else
		{
			std::cout << "l2: " << line << "\n";
			nodes.push_back(line);
		}
		
	}

	return 0;
}