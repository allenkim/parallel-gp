#ifndef __PARITY_H__
#define __PARITY_H__
#include <string>
#include <vector>
#include "parse_graph.h"
class ParseGraph;

const int WIDTH = 2;
const int HEIGHT = 4;
const int POP_SIZE = 2000;
const int NUM_GEN = 50;
const int TOURN_SIZE = 30;
const float CROSSOVER_PROB = 0.7;
const float GLOBAL_MUT_PROB = 0.05;
const float LINK_MUT_PROB = 0.05;
const float NODE_MUT_PROB = 0.05;

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
float fitness(ParseGraph*  p, bool print = false);
Value eval();


#endif
