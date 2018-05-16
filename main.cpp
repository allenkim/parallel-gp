#include <iostream>
#include <cstdio>
#include <ctime>
#include <omp.h>
#include "random.h"
#include "parse_graph.h"
#include "gp.h"
#include "xor.h"

unsigned int *state;



int main(){
	// Constants found in problem specific header
	init_rand_state(1);
	GP gp(POP_SIZE,NUM_GEN);
	gp.tournament_size = TOURN_SIZE;
	gp.crossover_prob = CROSSOVER_PROB;
	gp.global_mut_prob = GLOBAL_MUT_PROB;
	gp.link_mut_prob = LINK_MUT_PROB;
	gp.node_mut_prob = NODE_MUT_PROB;
	gp.initialize_pop(GRID_SIZE, true);
	gp.run(true);
	printf("\n");
	return 0;
}

/*
int main(){
	omp_set_num_threads(1);
	init_rand_state(1);
	ParseGraph* test1 = new ParseGraph();
	double start_time = omp_get_wtime();
	test1->generate_graph(3);
	test1->print_parse_graph();
	std::cout << value_to_string(test1->eval({FALSE,FALSE})) << std::endl;
	std::cout << "FITNESS: " << fitness(test1) << std::endl;
	double time = omp_get_wtime() - start_time;
	std::cout << "\t Time(ms): " << time*1000 << std::endl;
	delete test1;
	return 0;
}
*/

