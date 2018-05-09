#include <vector>
#include <cstdlib>
#include <string>
#include <iostream>
#include <iomanip>
#include "random.h"

/*This class represents the node objects, which will be used to populate the parse graph. A node will either be active or inactive, and can be
either a function or a terminal, and contains a set of pointers to its children. We may compute the value of a function node by recursing down
the value  of its children.
*/

Node::Node(){

}

Node::Node(bool active, bool terminal, int size): active(active), terminal(terminal) {
	if (this->terminal){
		node_type = rand(0) % num_terminal_types;
	}else {
		node_type = rand(0) % num_nonterminal_types;
		int num_children = num_arguments(static_cast<NonTerminal>(node_type));
		children = std::vector<int>(num_children);
		for (int i = 0; i < num_children; i++){
			children[i]= rand(0) % size;
		}
	}
}
std::string Node::toString(){
	std::string children_to_string = "";
	if (!this->terminal){
		for (unsigned int i = 0; i < this->children.size(); i++){
			children_to_string += (std::string(" ") + std::to_string(this->children[i]));
		}
	}
	return (std::string("Node: ") + (this->active ?"ON ":"OFF") + (this->terminal ? " T ":" NT" ) + " VALUE: " + type_to_string(this->terminal,this->node_type) + " CHILDREN: " + children_to_string);
}

ParseGraph::ParseGraph(const ParseGraph&){};

ParseGraph::~ParseGraph(){};

void ParseGraph::generate_graph(int size){
	this->size = size;
	graph = std::vector<std::vector<Node>>(size,std::vector<Node>(size)); //allocate memory for the graph (has size * size Node objects)
	output = Node(true, false, size); //setup the first node
	for (int i = 0; i < size-1; i++){ //generate children
		for (int j = 0; j < size; j++){
			if (rand(0) % 2){
				graph[i][j] = Node(false, true, size);
			}else{
				graph[i][j] = Node(false, false, size);
			}
		}
	}
	for (int i = 0; i < size; i++){
		graph[size-1][i] = Node(false,true, size);
	}
	//mark the active nodes
	for (unsigned int i = 0; i < output.children.size(); i++){
		graph[0][output.children[i]].active = true;
	}
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			if (graph[i][j].active){
				if (!graph[i][j].terminal){
					for (unsigned int k = 0; k < graph[i][j].children.size(); k++ ){
						graph[i+1][graph[i][j].children[k]].active = true;
					}
				}
			}
		}
	}
}

void ParseGraph::print_parse_graph(){
	std::cout << output.toString() << std::endl;
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			std::cout << std::left << std::setw(45) << graph[i][j].toString();
		}
		std::cout << std::endl;
	}
}

Value ParseGraph::eval(vector<Value> inputs){
	/*if (this){
		return
	}*/
	return Value::TRUE;
}
