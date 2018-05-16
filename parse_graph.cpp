#include <vector>
#include <cstdlib>
#include <string>
#include <iostream>
#include <iomanip>
#include "random.h"
#include "parse_graph.h"

/*This class represents the node objects, which will be used to populate the parse graph. A node will either be active or inactive, and can be
either a function or a terminal, and contains a set of pointers to its children. We may compute the value of a function node by recursing down
the value  of its children.
*/

Node::Node(){

}

Node::Node(bool active, bool terminal, int size): active(active), terminal(terminal){
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

Node::Node(const Node &rhs){
	terminal = rhs.terminal;
	active = rhs.active;
	node_type = rhs.node_type;
	children = rhs.children;
}

std::string Node::toString(){
	std::string children_to_string = "";
	if (!this->terminal){
		for (unsigned int i = 0; i < this->children.size(); i++){
			children_to_string += (std::string(" ") + std::to_string(this->children[i]));
		}
	}
	return (std::string("Node:") + (this->active ?"ON ":"OFF") + (this->terminal ? " T ":" NT" ) + " VALUE: " + type_to_string(this->terminal,this->node_type) + "CHILDREN: " + children_to_string);
}

void ParseGraph::mark_inactive(int i, int j){
	if (i >= this->size || j >= this->size)
		return;
	if (this->graph[i][j].active){
		this->graph[i][j].active = false;
		if (!graph[i][j].terminal){
			for (unsigned int k = 0; k < graph[i][j].children.size(); k++){
				this->mark_inactive(i+1, graph[i][j].children[k]);
			}
		}
	}
}


void ParseGraph::mark_active(int i, int j){
	if (i >= this->size || j >= this->size)
		return;
	if (!this->graph[i][j].active){
		this->graph[i][j].active = true;
		if (!graph[i][j].terminal){
			for (unsigned int k = 0; k < graph[i][j].children.size(); k++){
				this->mark_active(i+1, graph[i][j].children[k]);
			}
		}
	}
}

void ParseGraph::generate_graph(int size){
	this->size = size;
	graph = std::vector<std::vector<Node>>(size,std::vector<Node>(size)); //allocate memory for the graph (has size * size Node objects)
	output = Node(true, false, size); //setup the first node
	for (int i = 0; i < size-1; i++){ //generate children, for each row
		for (int j = 0; j < size; j++){  //for each columm
			if (rand(0) % 2){
				graph[i][j] = Node(false, true, size); //terminal node
			}else{
				graph[i][j] = Node(false, false, size); //non-terminal node
			}
		}
	}
	for (int i = 0; i < size; i++){
		graph[size-1][i] = Node(false,true, size);
	}
	for (unsigned int i = 0; i < output.children.size(); i++)
		this->mark_active(0,output.children[i]);
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

Value ParseGraph::eval(vector<Value> inputs) const{
	vector<Value> values = vector<Value>(this->size);
	//for the first row (of only terminals), determine the values of the terminals
	for (int j = 0; j < size; j++){
		if( graph[size-1][j].active){
			values[j] = inputs[graph[size-1][j].node_type];
		}
	}
	//for the next row, determine the values of the active nodes, based on the previous nodes
	//do this for all the following rows
	vector<Value> next_row_values;
	for (int i = size-2; i >= 0; i--){
		next_row_values = vector<Value>(this->size);
		for (int j = 0; j < size; j++){
			if (graph[i][j].active){
				if (graph[i][j].terminal){
					next_row_values[j] = inputs[graph[i][j].node_type];
				}else{ //if the node is a nonterminal
					vector<Value> input_to_this_function = vector<Value>(graph[i][j].children.size());
					for (unsigned int k = 0; k < graph[i][j].children.size(); k++){
						input_to_this_function[k] = values[graph[i][j].children[k]];
					}
					next_row_values[j] = compute_nonterminal((NonTerminal)graph[i][j].node_type, input_to_this_function);
				}
			}
		}
		values = next_row_values;
	}
	//finally, compute the output node
	vector<Value> input_to_this_function = vector<Value>(output.children.size());
	for (unsigned int k = 0; k < output.children.size(); k++){
		input_to_this_function[k] = values[output.children[k]];
	}
	return compute_nonterminal((NonTerminal)output.node_type, input_to_this_function);
}

ParseGraph* ParseGraph::copy(){
	ParseGraph* copyg = new ParseGraph();
	copyg->output = this->output;
	copyg->graph = this->graph;
	copyg->size = this->size;
	copyg->fitness = this->fitness;
	return copyg;
}
