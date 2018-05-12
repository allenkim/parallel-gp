#include <iostream>
#include <cstdio>
#include "gp.h"
#include "random.h"

extern float fitness(ParseGraph*);

float GP::initialize_pop(int grid_size){
	for (int i = 0; i < this->pop_size; i++){
		ParseGraph* g = new ParseGraph();
		g->generate_graph(grid_size);
		this->population.push_back(g);
	}
	return this->eval_fitness();
}

/* g1 is the dad and g2 is mom
 * dad dies and mom becomes child
 * also g1 and g2 should have same sizes
 */
void GP::crossover(ParseGraph* g1, ParseGraph* g2){
	if (randf(0) > this->crossover_prob)
		return;
	int cp1x = -1, cp1y = -1, cp2x = -1, cp2y = -1;
	unsigned int sample_count = 1;
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
	if (randf(0) > this->global_mut_prob)
		return;
	ParseGraph* tmp = new ParseGraph();
	tmp->generate_graph(g->size);
	this->crossover(tmp, g);
	delete tmp;
}

void GP::link_mutation(ParseGraph* g){
	if (randf(0) > this->link_mut_prob)
		return;
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
	g->graph[cp1x][cp1y].children[child_idx] = new_child;
	g->mark_active(cp1x+1,new_child);
}

float GP::eval_fitness(){
	float total = 0.0;
	for (int i = 0; i < this->pop_size; i++){
		if (this->population[i]->fitness < 0)
			this->population[i]->fitness = fitness(this->population[i]);
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
		this->crossover(dad,child);
		this->global_mutation(child);
		this->link_mutation(child);
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

float GP::run(){
	float score = -1.0;
	for (int i = 0; i < max_gen_num; i++){
		score = this->next_gen();
		printf("%f\n", score);
	}
	return score;
}

