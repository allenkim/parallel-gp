#include <iostream>
#include <cstdio>
#include "gp.h"
#include "random.h"

void GP::initialize_pop(int grid_size){
	for (int i = 0; i < this->pop_size; i++){
		ParseGraph* g = new ParseGraph();
		g->generate_graph(grid_size);
		this->population.push_back(g);
	}
}

/* g1 is the dad and g2 is mom
 * dad dies and mom becomes child
 * also g1 and g2 should have same sizes
 */
void GP::crossover(ParseGraph* g1, ParseGraph* g2){
	int cp1x = -1, cp1y = -1, cp2x = -1, cp2y = -1;
	int sample_count = 1;
	for (int i = 0; i < g1->size; i++){
		for (int j = 0; j < g1->size; j++){
			if (g1->graph[i][j].active){
				if (rand(0) % sample_count == sample_count - 1){
					cp1x = i;
					cp1y = j;
				}
			}
			if (g2->graph[i][j].active){
				if (rand(0) % sample_count == sample_count - 1){
					cp2x = i;
					cp2y = j;
				}
			}
		}
	}
	if (cp1x == -1 || cp2x == -1)
		return;
	//printf("%d %d, %d %d\n", cp1x, cp1y, cp2x, cp2y);
	g2->graph[cp2x][cp2y] = g1->graph[cp1x][cp1y];
	for (int i = cp2x+1; i < g2->size; i++){
		for (int j = 0; j < g2->size; j++){
			if (g1->graph[i][j].active)
				g2->graph[i][j] = g1->graph[i][j];
		}
	}
}

