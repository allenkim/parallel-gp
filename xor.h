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

Terminal microeval(NonTerminal id);
float fitness();
Terminal eval();

