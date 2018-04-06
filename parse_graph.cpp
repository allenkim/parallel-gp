#include <vector>
#include <rand>
#include <stdlib.h>
#include <time.h>

/*This class represents the node objects, which will be used to populate the parse graph. A node will either be active or inactive, and can be
either a function or a terminal, and contains a set of pointers to its children. We may compute the value of a function node by recursing down
the value  of its children.
*/
class Node{
	public:
		Node(bool _active, bool _terminal, vector<Node*> _children): active(_active), terminal(_terminal),children(_children) {
			if (_terminal){
				node_type = rand%(xor::num_terminal_types);
			}else{
				node_type = rand%(xor::num_nonterminal_types);
			}
		}
		Node(const Node&);
		~Node();
		bool active;
		bool terminal;
		//value for terminal or nonterminal depending
		int node_type;
		vector<Node*> children;
		Terminal microeval(){

		}
};

class Parse Graph{
	public:
		vector<vector<Node>> graph;
		int num_rows(){
			return graph.size();
		}
		initialize_graph(int size){
			srand(time(NULL));
			graph = vector<vector<Node>>(size,vector<Node>(size)); //allocate memory for the graph (has size * size Node objects)

			//setup the first node
			int node_type = rand%(xor::num_nonterminal_types);
			int num_args = xor::num_arguments(node_type);
			

			for (int i = 0; i < size; i++){ //generate children
				if (graph[1][i].active == NULL){

				}
			}
			graph[0][0] = Node(true,false,rand%(xor::));

		}

	private:


}
