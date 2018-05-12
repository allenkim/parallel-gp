#ifndef __PARSE_GRAPH_H__
#define __PARSE_GRAPH_H__
#include <vector>
#include "xor.h"
#include <string>
enum Value : int;
using std::vector;

class Node{
	public:
		Node();
		Node(bool active, bool terminal, int size);
		Node(const Node &rhs);
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
		void print_parse_graph();
		Node output;
		vector<vector<Node> > graph;
		int size;
		float fitness = -1.0;

		void mark_active(int i, int j);
		void generate_graph(int size);
		void print_output();
		ParseGraph* copy();
		Value eval(vector<Value>) const;
};

#endif
