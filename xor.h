#ifndef __XOR_H__
#define __XOR_H__
#include <string>

enum Terminal{
	X1,
	X2
};

enum Value{
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

const int num_terminal_types = 2;
const int num_nonterminal_types = 6;

int num_arguments(NonTerminal non_terminal_type);
std::string type_to_string(bool terminal, int id);
float fitness();
Value eval();

#endif
