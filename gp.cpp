#include "gp.h"

void GP::initialize_pop(int grid_size){
	for (int i = 0; i < this->pop_size; i++){
		ParseGraph* g = new ParseGraph();
		g->generate_graph(grid_size);
		this->population.push_back(g);
	}
}

