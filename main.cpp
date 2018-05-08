#include <iostream>
#include <cstdio>
#include <ctime>
#include "random.h"
#include "parse_graph.h"

int *state;

int main(){
	init_rand_state(1);
	ParseGraph test = ParseGraph();
	test.generate_graph(3);
	test.print_parse_graph();
	return 0;
}
