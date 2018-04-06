enum Terminal{
	FALSE,
	TRUE
}
enum NonTerminal{
	AND,
	NAND,
	OR,
	NOR,
	NOT
}

int num_terminal_types = 2;
int num_nonterminal_types = 5;

int num_arguments(NonTerminal non_terminal_type){
	if (non_terminal_type != NonTerminal.NOT){
		return 2;
	}
	return 1;
}

Terminal microeval(NonTerminal id);
float fitness();
Terminal eval();
