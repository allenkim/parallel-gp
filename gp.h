#ifndef __GP_H__
#define __GP_H__
#include <vector>
#include "parse_graph.h"

using std::vector;

class GP{
	public:
		GP();
		~GP();

		vector<ParseGraph*> population;
		int gen_num;

		void next_gen();
		vector<ParseGraph*> selection(vector<ParseGraph*> pop, int num_survivors);
		ParseGraph* crossover(ParseGraph* p1, ParseGraph* p2);
		void mutation(ParseGraph* g);
};

#endif

