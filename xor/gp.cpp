#include <iostream>
#include <cstdio>
#include "gp.h"
#include "random.h"

extern float fitness(ParseGraph*);

GP::~GP(){
	for (unsigned int i = 0; i < this->population.size(); i++){
		delete this->population[i];
	}
	delete this->best;
}

float GP::initialize_pop(int width, int height, bool verbose){
	if (this->population.size() > 0){
		for (int i = 0; i < this->pop_size; i++){
			delete population[i];
		}
		this->population.clear();
	}
	for (int i = 0; i < this->pop_size; i++){
		ParseGraph* g = new ParseGraph();
		g->generate_graph(width, height);
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
	unsigned int sample_count = 2;
	for (int i = 0; i < g1->height; i++){
		for (int j = 0; j < g1->width; j++){
			if (g1->graph[i][j].active){
				if (xorand() % sample_count == sample_count - 1){
					cp1x = i;
					cp1y = j;
				}
				sample_count++;
			}
		}
	}
	sample_count = 2;
	for (int i = 0; i < g1->height; i++){
		for (int j = 0; j < g1->width; j++){
			if (g2->graph[i][j].active){
				if (xorand() % sample_count == sample_count - 1){
					cp2x = i;
					cp2y = j;
				}
				sample_count++;
			}
		}
	}
	//printf("%d %d, %d %d\n", cp1x, cp1y, cp2x, cp2y);
	if (cp2x == g2->height - 1)
		return;
	if (cp1x == -1){
		if (cp2x == -1){
			g2->output = g1->output;
			g2->graph = g1->graph;
		}
		else{
			g2->graph[cp2x][cp2y] = g1->output;
		}
	}
	else if (cp2x == -1){
		if (g1->graph[cp1x][cp1y].terminal)
			return;
		g2->output = g1->graph[cp1x][cp1y];
	}
	else{
		g2->graph[cp2x][cp2y] = g1->graph[cp1x][cp1y];
	}
	for (int i = cp2x+1; i < g2->height - 1; i++){
		for (int j = 0; j < g2->width; j++){
			int g1idx = i-cp2x+cp1x;
			if (g1idx < g1->height && g1->graph[g1idx][j].active)
				g2->graph[i][j] = g1->graph[g1idx][j];
		}
	}
}

ParseGraph* GP::selection(int tournament_size){
	if (tournament_size > this->pop_size)
		tournament_size = this->pop_size;
	ParseGraph* best = NULL;
	float best_fitness = -1.0;
	for (int i = 0; i < tournament_size; i++){
		int r = xorand() % this->pop_size;
		if (this->population[r]->fitness > best_fitness){
			best = this->population[r];
			best_fitness = this->population[r]->fitness;
		}
	}
	return best;
}

void GP::global_mutation(ParseGraph* g){
	ParseGraph* tmp = new ParseGraph();
	tmp->generate_graph(g->width,g->height);
	this->crossover(tmp, g);
	delete tmp;
}

void GP::link_mutation(ParseGraph* g){
	unsigned int sample_count = 1;
	int cp1x = -1, cp1y = -1, child_idx = -1;
	for (int i = 0; i < g->height; i++){
		for (int j = 0; j < g->width; j++){
			int num_child = g->graph[i][j].children.size();
			if (g->graph[i][j].active && num_child > 0){
				for (int k = 0; k < num_child; k++){
					if (xorand() % sample_count == sample_count - 1){
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
	int new_child = xorand() % g->width;
	g->mark_inactive(cp1x+1, child_idx);
	g->graph[cp1x][cp1y].children[child_idx] = new_child;
	//printf("%d %d %d %d\n", cp1x, cp1y, child_idx, new_child);
	g->mark_active(cp1x+1,new_child);
}

void GP::node_mutation(ParseGraph* g){
	unsigned int sample_count = 2;
	int cp1x = -1, cp1y = -1;
	for (int i = 0; i < g->height; i++){
		for (int j = 0; j < g->width; j++){
			if (g->graph[i][j].active){
				if (xorand() % sample_count == sample_count - 1){
					cp1x = i;
					cp1y = j;
				}
			}
		}
	}
	if (cp1x == -1){
		g->output = Node(false,false,g->width,g->height);
		for (int i = 0; i < g->height; i++){
			g->mark_inactive(0,i);
		}
		for (unsigned int i = 0; i < g->output.children.size(); i++){
			g->mark_active(0,g->output.children[i]);
		}
	}
	else{
		g->mark_inactive(cp1x, cp1y);
		if (cp1x == g->height - 1)
			g->graph[cp1x][cp1y] = Node(false, true, g->width, g-> height);
		else{
			if (xorand() % 2){
				g->graph[cp1x][cp1y] = Node(false, true, g->width, g-> height); //terminal node
			}else{
				g->graph[cp1x][cp1y] = Node(false, false, g->width, g-> height); //non-terminal node
			}
		}
		g->mark_active(cp1x,cp1y);
	}
}

float GP::eval_fitness(){
	float total = 0.0;
	#pragma omp parallel for
	for (int i = 0; i < this->pop_size; i++){
		if (this->population[i]->fitness < 0)
			this->population[i]->fitness = fitness(this->population[i]);
		if (this->population[i]->fitness > this->best_fitness){
			#pragma omp critical
			{
				this->best_fitness = this->population[i]->fitness;
				if (this->best)
					delete this->best;
				this->best = this->population[i]->copy();
			}
		}
		#pragma omp atomic
		total += this->population[i]->fitness;
	}
	return total / this->pop_size;
}

float GP::next_gen(){
	this->tmp_pop.clear();
	this->tmp_pop.resize(this->pop_size);
	#pragma omp parallel for
	for (int i = 0; i < this->pop_size; i++){
		ParseGraph *dad, *mom, *child;
		dad = this->selection(this->tournament_size);
		mom = this->selection(this->tournament_size);
		child = mom->copy();
		child->fitness = -1.0;
		if (xorandf() <= this->crossover_prob){
			this->crossover(dad,child);
			//printf("Crossover\n");
		}
		if (xorandf() <= this->global_mut_prob){
			this->global_mutation(child);
			//printf("Global Mutation\n");
		}
		if (xorandf() <= this->link_mut_prob){
			this->link_mutation(child);
			//printf("Link Mutation\n");
		}
		if (xorandf() <= this->node_mut_prob){
			this->node_mutation(child);
			//printf("Node Mutation\n");
		}
		this->tmp_pop[i] = child;
	}
	#pragma omp parallel for
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
