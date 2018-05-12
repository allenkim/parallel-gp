#ifndef __PARSE_GRAPH_H__
#define __PARSE_GRAPH_H__
#include <vector>
#include "xor.h"
#include <string>

using std::vector;

class Node{
	public:
		Node();
		Node(bool active, bool terminal, int size);
		std::string toString();
		bool active;
		bool terminal;
		//node value (if it is a terminal)
		//value for terminal or nonterminal depending
		int node_type;
		vector<int> children;
};

class ParseGraph{
	public:
		ParseGraph() : size(0) {};
		ParseGraph(const ParseGraph&);
		~ParseGraph();
		void print_parse_graph();
		Node output;
		vector<vector<Node> > graph;
		int size;

		void generate_graph(int size);
		void print_output();
		float fitness();
		Value eval(vector<Value>);
};

#endif
