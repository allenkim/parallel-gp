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

class GP{
	public:
		GP();
		~GP();

		vector<ParseGraph*> population;
		int gen_num;

		void next_gen();
		vector<ParseGraph*> selection(vector<ParseGraph*> pop, int num_survivors);
		ParseGraph* crossover(ParseGraph* p1, ParseGraph* p2);
		void mutation(ParseGraph* g);
};

