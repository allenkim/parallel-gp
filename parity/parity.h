#ifndef __PARITY_H__
#define __PARITY_H__
#include <string>
#include <vector>
#include "parse_graph.h"
class ParseGraph;

const int WIDTH = 3;
const int HEIGHT = 3;
const int POP_SIZE = 200;
const int NUM_GEN = 5;
const int TOURN_SIZE = 7;
const float CROSSOVER_PROB = 0.7;
const float GLOBAL_MUT_PROB = 0.3;
const float LINK_MUT_PROB = 0.3;
const float NODE_MUT_PROB = 0.3;

enum Terminal{
	X1,
	X2,
  X3
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

const unsigned int num_terminal_types = 3;
const unsigned int num_nonterminal_types = 6;
const unsigned int num_values = 2;

unsigned int num_arguments(NonTerminal non_terminal_type);
std::string type_to_string(bool terminal, int id);
std::string value_to_string(Value);
Value compute_nonterminal(NonTerminal,std::vector<Value>);
float fitness(ParseGraph*  p);
Value eval();


#endif
