#include <vector>
#include "xor.h"

using std::vector;

class Node{
	public:
		Node();
		Node(bool active, bool terminal, vector<Node*> children);
		Node(const Node&);
		~Node();

		bool active;
		bool terminal;
		//value for terminal or nonterminal depending
		int node_type;
		vector<Node*> children;

		Terminal microeval();
};

class ParseGraph{
	public:
		ParseGraph() : num_rows(0) {};
		ParseGraph(const ParseGraph&);
		~ParseGraph();
		Node output;
		vector<vector<Node> > graph;
		int num_rows;

		void generate_graph(int size);
		float fitness();
		Terminal eval();
};
