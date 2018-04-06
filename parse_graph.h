#include "xor.h"

class Node{
	public:
		Node();
		Node(const Node&);
		~Node();

		bool active;
		bool terminal;
		//value for terminal or nonterminal depending
		int node_type; 
		Terminal microeval();
};

class ParseGraph{
	public:
		ParseGraph();
		~ParseGraph();

		void init_random();
		float fitness();
		Terminal eval();
};

