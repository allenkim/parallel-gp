#include <iostream>
#include <cstdio>
#include "gp.h"
#include "random.h"

extern float fitness(ParseGraph*);

GP::~GP(){
	for (int i = 0; i < pop_size; i++){
		delete this->population[i];
	}
	delete this->best;
}

float GP::initialize_pop(int grid_size, bool verbose){
	if (this->population.size() > 0){
		for (int i = 0; i < this->pop_size; i++){
			delete population[i];
		}
		this->population.clear();
	}
	for (int i = 0; i < this->pop_size; i++){
		ParseGraph* g = new ParseGraph();
		g->generate_graph(grid_size);
		this->population.push_back(g);
	}
	float fitness = this->eval_fitness();
	if (verbose)
		printf("Gen 0: %f\n", fitness);
	return fitness;
}

/* g1 is the dad and g2 is mom
 * dad dies and mom becomes child
 * also g1 and g2 should have same sizes
 * SSIAN
 */
void GP::crossover(ParseGraph* g1, ParseGraph* g2){
	int cp1x = -1, cp1y = -1;
	int cp2x = -1, cp2y = -1;
	unsigned int sample_count = 1;
	for (int i = 0; i < g1->size; i++){
		for (int j = 0; j < g1->size; j++){
			if (g1->graph[i][j].active){
				if (rand(0) % sample_count == sample_count - 1){
					cp2x = i;
					cp2y = j;
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

ParseGraph* GP::selection(int tournament_size){
	if (tournament_size > this->pop_size)
		tournament_size = this->pop_size;
	int s = tournament_size;
	int left = this->pop_size;
	int start = 0;
	while (s--){
		int r = start;
		r += rand(0) % left;
		ParseGraph* tmp = this->population[r];
		this->population[r] = this->population[start];
		this->population[start] = tmp;
		++start;
		--left;
	}
	ParseGraph* best = this->population[0];
	for (int i = 1; i < tournament_size; i++){
		if (this->population[i]->fitness > best->fitness){
			best = this->population[i];
		}
	}
	return best;
}

void GP::global_mutation(ParseGraph* g){
	ParseGraph* tmp = new ParseGraph();
	tmp->generate_graph(g->size);
	this->crossover(tmp, g);
	delete tmp;
}

void GP::link_mutation(ParseGraph* g){
	unsigned int sample_count = 1;
	int cp1x = -1, cp1y = -1, child_idx = -1;
	for (int i = 0; i < g->size; i++){
		for (int j = 0; j < g->size; j++){
			int num_child = g->graph[i][j].children.size();
			if (g->graph[i][j].active && num_child > 0){
				for (int k = 0; k < num_child; k++){
					if (rand(0) % sample_count == sample_count - 1){
						cp1x = i;
						cp1y = j;
						child_idx = k;
					}
				}
			}
		}
	}
	if (cp1x == -1)
		return;
	int new_child = rand(0) % g->size;
	g->mark_inactive(cp1x+1, child_idx);
	g->graph[cp1x][cp1y].children[child_idx] = new_child;
	//printf("%d %d %d %d\n", cp1x, cp1y, child_idx, new_child);
	g->mark_active(cp1x+1,new_child);
}

void GP::node_mutation(ParseGraph* g){
	unsigned int sample_count = 1;
	int cp1x = -1, cp1y = -1;
	for (int i = 0; i < g->size; i++){
		for (int j = 0; j < g->size; j++){
			if (g->graph[i][j].active){
				if (rand(0) % sample_count == sample_count - 1){
					cp1x = i;
					cp1y = j;
				}
			}
		}
	}
	if (cp1x == -1)
		return;
	g->mark_inactive(cp1x, cp1y);
	if (cp1x == g->size - 1)
		g->graph[cp1x][cp1y] = Node(false, true, g->size);
	else{
		if (rand(0) % 2){
			g->graph[cp1x][cp1y] = Node(false, true, g->size); //terminal node
		}else{
			g->graph[cp1x][cp1y] = Node(false, false, g->size); //non-terminal node
		}
	}
	g->mark_active(cp1x,cp1y);

}

float GP::eval_fitness(){
	float total = 0.0;
	for (int i = 0; i < this->pop_size; i++){
		if (this->population[i]->fitness < 0)
			this->population[i]->fitness = fitness(this->population[i]);
		if (this->population[i]->fitness > this->best_fitness){
			this->best_fitness = this->population[i]->fitness;
			if (this->best)
				delete this->best;
			this->best = this->population[i]->copy();
		}
		total += this->population[i]->fitness;
	}
	return total / this->pop_size;
}

float GP::next_gen(){
	this->tmp_pop.clear();
	ParseGraph *dad, *mom, *child;
	for (int i = 0; i < this->pop_size; i++){
		dad = this->selection(this->tournament_size);
		mom = this->selection(this->tournament_size);
		child = mom->copy();
		if (randf(0) <= this->crossover_prob)
			this->crossover(dad,child);
		if (randf(0) <= this->global_mut_prob)
			this->global_mutation(child);
		if (randf(0) <= this->link_mut_prob)
			this->link_mutation(child);
		if (randf(0) <= this->node_mut_prob)
			this->node_mutation(child);
		this->tmp_pop.push_back(child);
	}
	for (int i = 0; i < this->pop_size; i++){
		delete this->population[i];
	}
	this->population = this->tmp_pop;
	float avg_fitness = this->eval_fitness();
	this->curr_gen_num++;
	return avg_fitness;
}

float GP::run(bool verbose){
	float score = -1.0;
	for (int i = 0; i < max_gen_num; i++){
		score = this->next_gen();
		if (verbose)
			printf("Gen %d: %f\n", this->curr_gen_num, score);
	}
	return score;
}

