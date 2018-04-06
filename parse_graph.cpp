#include <vector>
#include <random>
#include <cstdlib>
#include <string>
#include "parse_graph.h"

/*This class represents the node objects, which will be used to populate the parse graph. A node will either be active or inactive, and can be
either a function or a terminal, and contains a set of pointers to its children. We may compute the value of a function node by recursing down
the value  of its children.
*/

Node::Node(){

}

Node::Node(bool active, bool terminal): active(active), terminal(terminal) {
	if (this->terminal){
		node_type = rand() % num_terminal_types;
	}else {
		node_type = rand() % num_nonterminal_types;
		int num_children = int num_arguments(static_cast<NonTerminal> node_type);
		children = std::vector<int>(num_children);
		for (int i = 0; i < num_children; i++){
			children[i]= rand() % size;
		}
	}
}

Node::Node(const Node& node){

}

Node::~Node(){
	for (Node* child : children)
		delete child;
}

std::string Node::toString(){
	if ()
	return ("Node: " + (this->active ?"ACTIVE":"INACTIVE") + (this->terminal ? "TERMINAL":"NONTERMINAL" ) + "VALUE: " + type_to_string(this->terminal,this->node_type) + );
}

Terminal Node::microeval(){
	// Need to call global microeval with appropriate id
	return Terminal::FALSE;
}

void ParseGraph::generate_graph(int size){
	graph = std::vector<std::vector<Node>>(size,std::vector<Node>(size)); //allocate memory for the graph (has size * size Node objects)
	output = Node(true, false);
	//setup the first node
	for (int i = 0; i < size-1; i++){ //generate children
		for (int j = 0; j < size; j++){
			if (rand() % 2){
				graph[i][j] = Node(false, true);
			}else{
				graph[i][j] = Node(false, false);
			}
		}
	}
	for (int i = 0; i < size; i++){
		graph[size-1][i] = Node(false,true);
	}
}

void ParseGraph::print_parse_graph(){
	cout << output

}
