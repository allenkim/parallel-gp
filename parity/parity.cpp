#include "parity.h"
#include <omp.h>
#include <string>
#include <cmath>
#include <iostream>
#include <iomanip>

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
		    case 2:
        		return "X3   ";
			case 3:
				return "X4   ";
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

//even number of 0s returns a 1
unsigned int parity(unsigned int x){
	x ^= x >> 16;
	x ^= x >> 8;
	x ^= x >> 4;
	x ^= x >> 2;
	x ^= x >> 1;
	return ((~x) & 1);
}


float fitness(ParseGraph* p, bool print){
	int hamming_distance = 0;
	vector<vector<Value>> A(pow(2,num_terminal_types),vector<Value>(num_terminal_types));
	if (print){
		std::cout << "======================" << std::endl;
		std::cout << "Printing truth table for the parse graph: " << std::endl;
		for (unsigned int i = 0; i < num_terminal_types; i++){
			std::cout << std::setw(9) << type_to_string(true,i);
		}
		std::cout << std::setw(9)<< "Output:" << "Expected output (parity checker):" << std::endl;
	}
	for (unsigned int i = 0; i < pow(2,num_terminal_types); i++){
		//std::cout << "i: " << i << std::endl;
		//std::cout << "parity[i]: " << parity(i) << std::endl;
		for (unsigned int j = 0; j < num_terminal_types; j++){
			if (((1 << j) & i) > 0){
				A[i][num_terminal_types-1-j] = TRUE;
			}else{
				A[i][num_terminal_types-1-j] = FALSE;
			}
		}
		if (print){
			for (unsigned int j = 0; j < num_terminal_types; j++){
					std::cout << std::setw(9) << value_to_string(A[i][j]);
			}
		}
		//for (unsigned int j = 0; j < num_terminal_types; j++){
		//	std::cout << value_to_string(A[i][j]) << " ";
		//}
		//std::cout << std::endl;
	  //	std::cout << "\t\tp->eval(A[i]) " << value_to_string(p->eval(A[i])) << std::endl;
		Value v,y;
		if ((v = p->eval(A[i])) != (y = ((parity(i) == 0) ?  TRUE:FALSE))) {
			 //std::cout << "MATCH" <<  std::endl;
			hamming_distance++;
		}
		if (print)
			std::cout << std::setw(9) << value_to_string(v) <<  value_to_string(y) << std::endl;
	}
	return pow(2,num_terminal_types) - hamming_distance;
}

Value eval(){
	return Value::FALSE;
}
