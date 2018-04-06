#ifndef __PARSE_GRAPH_H__
#define __PARSE_GRAPH_H__
#include <vector>
#include "xor.h"

using std::vector;

class Node{
	public:
		Node();
		Node(bool active, bool terminal, vector<int> children);
		Node(const Node&);
		~Node();

		bool active;
		bool terminal;
		//value for terminal or nonterminal depending
		int node_type; 
		vector<int> children;

		Terminal microeval();
};

class ParseGraph{
	public:
		ParseGraph() : size(0) {};
		ParseGraph(const ParseGraph&);
		~ParseGraph();

		Node output;
		vector<vector<Node> > graph;
		int size;

		void generate_graph(int size);
		float fitness();
		Terminal eval();
};

#endif

