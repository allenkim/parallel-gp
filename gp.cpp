#include <random>
#include <utility>
#include "gp.h"

typedef std::pair<int,int> ii;

void GP::initialize_pop(int grid_size){
	for (int i = 0; i < this->pop_size; i++){
		ParseGraph* g = new ParseGraph();
		g->generate_graph(grid_size);
		this->population.push_back(g);
	}
}

/* g1 is the dad and g2 is mom
 * dad dies and mom becomes child
 */
void GP::crossover(ParseGraph* g1, ParseGraph* g2){
	ii crosspoint1;
	for (int i = 0; i < g1->size; i++){
		for (int j = 0; j < g1->size; j++){
			if (g1->graph[i][j].active){
				crosspoint1 = std::make_pair(i,j);
			}
		}
	}
}

