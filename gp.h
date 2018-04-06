#ifndef __GP_H__
#define __GP_H__
#include <vector>
#include "parse_graph.h"

using std::vector;

class GP{
	public:
		GP(int pop_size, int max_gen_num) : pop_size(pop_size), max_gen_num(max_gen_num) {}
		~GP();

		vector<ParseGraph*> population;
		int pop_size;
		int max_gen_num;
		float crossover_prob = 0.0;
		float global_mut_prob = 0.0;
		float link_mut_prob = 0.0;

		int curr_gen_num = 0;

		void initialize_pop(int grid_size);
		ParseGraph* selection();
		void crossover(ParseGraph* g1, ParseGraph* g2);
		void mutation(ParseGraph* g);
		void next_gen();
	private:
		vector<ParseGraph*> tmp_pop;
};

#endif

