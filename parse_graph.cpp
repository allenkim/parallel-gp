#include <vector>
#include <random>
#include <cstdlib>
#include "parse_graph.h"

/*This class represents the node objects, which will be used to populate the parse graph. A node will either be active or inactive, and can be
either a function or a terminal, and contains a set of pointers to its children. We may compute the value of a function node by recursing down
the value  of its children.
*/

Node::Node(){

}

Node::Node(bool active, bool terminal, vector<Node*> children): active(active), terminal(terminal),children(children) {
	if (this->terminal)
		node_type = rand() % (num_terminal_types);
	else
		node_type = rand() % (num_nonterminal_types);
}

Node::Node(const Node& node){

}

Node::~Node(){
	for (Node* child : children)
		delete child;
}

Terminal Node::microeval(){
	// Need to call global microeval with appropriate id
	return Terminal::FALSE;
}

void ParseGraph::generate_graph(int size){
	graph = vector<vector<Node>>(size,vector<Node>(size)); //allocate memory for the graph (has size * size Node objects)

	//setup the first node
	NonTerminal node_type = static_cast<NonTerminal>(rand() % num_nonterminal_types);
	int num_args = num_arguments(node_type);
	(void)num_args;
	/*
	for (int i = 0; i < size; i++){ //generate children
		if (graph[1][i].active == NULL){

		}
	}
	graph[0][0] = Node(true,false,rand()%(xor::));*/
}

