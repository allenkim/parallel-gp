#include <vector>
#include "xor.h"

using std::vector;

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

		vector<vector<Node*> > grid;	
		void init_random();
		float fitness();
		Terminal eval();
};

