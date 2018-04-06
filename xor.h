enum Terminal{
	FALSE,
	TRUE
};

enum NonTerminal{
	AND,
	NAND,
	OR,
	NOR,
	NOT
};

const int num_terminal_types = 2;
const int num_nonterminal_types = 5;

int num_arguments(NonTerminal non_terminal_type);
Terminal microeval(NonTerminal id);
float fitness();
Terminal eval();
