#include <iostream>
#include <cstdio>
#include <ctime>
#include <omp.h>
#include "random.h"
#include "parse_graph.h"
#include "gp.h"
unsigned int *state;
int NUM_THREADS;

// Constants found in problem specific header

ParseGraph* find_best_fit(bool verbose, bool det, int seed = 1){
	init_rand_state(NUM_THREADS, det, seed);
	GP gp(NUM_THREADS, POP_SIZE,NUM_GEN);
	gp.tournament_size = TOURN_SIZE;
	gp.crossover_prob = CROSSOVER_PROB;
	gp.global_mut_prob = GLOBAL_MUT_PROB;
	gp.link_mut_prob = LINK_MUT_PROB;
	gp.node_mut_prob = NODE_MUT_PROB;
	gp.initialize_pop(WIDTH, HEIGHT, verbose);
	gp.run(verbose);
	if (verbose)
		printf("Fitness: %f\n", gp.best_fitness);
	/*
	for (int i = 0; i < POP_SIZE; i++){
		gp.population[i]->print_parse_graph();
	}*/
	return gp.best->copy();
}

ParseGraph* find_best_fit_ensemble(int size, bool det, bool verbose = false){
	ParseGraph* global_best = NULL;
	float global_fitness = -1.0;
	#pragma omp parallel for
	for (int i = 0; i < size; i++){
		ParseGraph* best = find_best_fit(verbose, det, i);
		#pragma omp critical
		{
			if (best->fitness > global_fitness){
				if (global_best)
					delete global_best;
				global_best = best;
				global_fitness = best->fitness;
			}
		}
	}
	return global_best;
}


int main(int argc, char* argv[]){
	NUM_THREADS = 1;
	if (argc >= 2)
		NUM_THREADS = atoi(argv[1]);
	omp_set_num_threads(NUM_THREADS);
	double start_time = omp_get_wtime();
	//ParseGraph* best = find_best_fit_ensemble(100, false, false);
	ParseGraph* best = find_best_fit(true, false);
	double total_time = omp_get_wtime() - start_time;
	printf("Fitness: %f\n", best->fitness);
	best->print_parse_graph();
	printf("Time: %gs\n", total_time);
	return 0;
}

/*
int main(){
	init_rand_state(1, false, 1);
	ParseGraph* test1 = new ParseGraph();
	ParseGraph* test2 = new ParseGraph();
	test1->generate_graph(3);
	test2->generate_graph(3);
	GP gp(2,5);
	test1->print_parse_graph();
	test2->print_parse_graph();
	gp.crossover(test1,test2);
	test2->print_parse_graph();
	return 0;
}
*/

/*int main(){
	NUM_THREADS = 4;
	init_rand_state(NUM_THREADS, false);
	omp_set_num_threads(4);
	ParseGraph* test1 = new ParseGraph();
	double start_time = omp_get_wtime();
	test1->generate_graph(2,3);
	test1->print_parse_graph();
	std::cout << value_to_string(test1->eval({FALSE,FALSE})) << std::endl;
	std::cout << "FITNESS: " << fitness(test1) << std::endl;
	double time = omp_get_wtime() - start_time;
	std::cout << "\t Time(ms): " << time*1000 << std::endl;
	delete test1;
	return 0;
}*/
