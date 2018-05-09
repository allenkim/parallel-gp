#include <iostream>
#include <cstdio>
#include <ctime>
#include "random.h"
#include "parse_graph.h"
#include "gp.h"

int *state;

int main(){
	init_rand_state(1);
	ParseGraph* test1 = new ParseGraph();
	ParseGraph* test2 = new ParseGraph();
	test1->generate_graph(3);
	test2->generate_graph(3);
	test1->print_parse_graph();
	printf("\n");
	test2->print_parse_graph();
	GP gp(2,5);
	gp.crossover(test1, test2);
	printf("\n");
	test2->print_parse_graph();
	delete test1;
	delete test2;
	return 0;
}
