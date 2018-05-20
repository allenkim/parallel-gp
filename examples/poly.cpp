#include "poly.h"
#include <omp.h>
#include <string>
#include <iostream>

unsigned int num_arguments(NonTerminal non_terminal_type){
	if (non_terminal_type != NonTerminal::NOT){
		if (non_terminal_type != NonTerminal::I){
				return 2;
		}
	}
	return 1;
}

std::string type_to_string(bool terminal, int id){
	if (terminal){
		switch (id) {
			case 0:
				return "X1   ";
			case 1:
				return "X2   ";
			default:
					std::cout << id << std::endl;
					std::cout << "ERROR in function type_to_string. Invalid ID." << std::endl;
					exit(1);
		}
	}else{
		switch (id) {
			case 0:
				return "AND  ";
			case 1:
				return "NAND ";
			case 2:
				return "OR   ";
			case 3:
				return "NOR  ";
			case 4:
				return "NOT  ";
			case 5:
				return "I    ";
			default:
				std::cout << "ERROR in function type_to_string. Invalid ID." << std::endl;
				exit(1);
		}
	}
}

std::string value_to_string(Value value){
	if (value == TRUE){
		return "TRUE";
	}
	return "FALSE";
}

Value compute_nonterminal(NonTerminal non_terminal_type,std::vector<Value> inputs){
	if (inputs.size() != num_arguments(non_terminal_type))
		std::cout << "The given non-terminal does not have the same arguments as the provided inputs." << std::endl;
	switch(non_terminal_type){
		case AND:
			if ((inputs[0] == TRUE)&&(inputs[1] == TRUE))
				return TRUE;
			return FALSE;
			break;
		case NAND:
			if ((inputs[0] == TRUE)&&(inputs[1] == TRUE))
				return FALSE;
			return TRUE;
			break;
		case OR:
			if ((inputs[0] == TRUE)||(inputs[1] == TRUE))
				return TRUE;
			return FALSE;
			break;
		case NOR:
			if ((inputs[0] == TRUE)||(inputs[1] == TRUE))
				return FALSE;
			return TRUE;
			break;
		case NOT:
			if (inputs[0] == TRUE){
				return FALSE;
			}
			return TRUE;
			break;
		case I:
			return inputs[0];
			break;
		default:
			std::cout << "Error. Invalid argument in function compute_nonterminal." << std::endl;
			break;
	}
	std::cout << "ERROR. Reached code that should never be reached in function  compute_nonterminal" << std::endl;
	return FALSE;
}

float fitness(ParseGraph* p){
	int hamming_distance = 0;
	//vector<vector<Value>> = {{FALSE,FALSE},{FALSE,TRUE},{TRUE,FALSE},{TRUE,TRUE}};
	#pragma omp parallel
		{
			#pragma omp single nowait
			{
				if (p->eval({FALSE,FALSE}) == TRUE){
					#pragma omp atomic
					hamming_distance++;
				}
			}
			#pragma omp single nowait
			{
				if (p->eval({TRUE,FALSE}) == FALSE){
					#pragma omp atomic
					hamming_distance++;
				}
			}
			#pragma omp single nowait
			{
				if (p->eval({FALSE,TRUE}) == FALSE){
					#pragma omp atomic
					hamming_distance++;
				}
			}
			#pragma omp single nowait
			{
				if (p->eval({TRUE,TRUE}) == TRUE){
					#pragma omp atomic
					hamming_distance++;
				}
			}
		}
	return 4-hamming_distance;
}

Value eval(){
	return Value::FALSE;
}