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

string type_to_string(bool terminal, int id){
	if (terminal){
		switch (id) {
			case 0:
				return "FALSE";
			case 1:
				return "TRUE";
			default:
					std::cout << "ERROR in function type_to_string. Invalid ID." << std::endl;
					exit();
		}
	}else{
		switch (id) {
			case 0:
				return "AND";
			case 1:
				return "NAND";
			case 2:
				return "OR";
			case 3:
				return "NOR";
			case 4:
				return "NOT";
			case 5:
				return "I";
			default:
				std::cout << "ERROR in function type_to_string. Invalid ID." << std::endl;
				exit();
		}
	}
}

float fitness(){
	return 0.0;
}

Terminal eval(){
	return Terminal::FALSE;
}
