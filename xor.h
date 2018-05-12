#ifndef __XOR_H__
#define __XOR_H__
#include <string>
#include <vector>
#include "parse_graph.h"
class ParseGraph;

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
