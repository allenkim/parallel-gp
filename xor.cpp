#include "xor.h"

int num_arguments(NonTerminal non_terminal_type){
	if (non_terminal_type != NonTerminal::NOT){
		return 2;
	}
	return 1;
}


Terminal microeval(NonTerminal id){
	return Terminal::FALSE;
}

float fitness(){
	return 0.0;
}

Terminal eval(){
	return Terminal::FALSE;
}


