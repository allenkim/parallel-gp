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
	init_rand_state(1);
	GP gp(200,100);
	float score = gp.initialize_pop(3);
	printf("%f\n", score);
	gp.run();
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

