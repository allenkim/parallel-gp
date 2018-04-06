#include <iostream>
#include <cstdio>
#include <ctime>
#include "parse_graph.h"

int main(){
	srand(time(NULL));
	ParseGraph test = ParseGraph();
	test.generate_graph(3);
	test.print_parse_graph();
	return 0;
}
