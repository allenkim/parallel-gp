#ifndef __POLY_H__
#define __POLY_H__
#include <string>
#include <vector>
#include "parse_graph.h"
class ParseGraph;

const int GRID_SIZE = 6;
const int POP_SIZE = 1000;
const int NUM_GEN = 100;
const int TOURN_SIZE = 7;
const float CROSSOVER_PROB = 0.7;
const float GLOBAL_MUT_PROB = 0.25;
const float LINK_MUT_PROB = 0.25;
const float NODE_MUT_PROB = 0.05;

enum Terminal{
	X1,
	X2
};

enum Value: int {
	TRUE,
	FALSE
};

enum NonTerminal{
	AND,
	NAND,
	OR,
	NOR,
	NOT,
	I
};

const unsigned int num_terminal_types = 2;
const unsigned int num_nonterminal_types = 6;
const unsigned int num_values = 2;

unsigned int num_arguments(NonTerminal non_terminal_type);
std::string type_to_string(bool terminal, int id);
std::string value_to_string(Value);
Value compute_nonterminal(NonTerminal,std::vector<Value>);
float fitness(ParseGraph*  p);
Value eval();

#endif