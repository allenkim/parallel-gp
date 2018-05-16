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
		int tournament_size = 5;
		float crossover_prob = 0.7;
		float global_mut_prob = 0.25;
		float link_mut_prob = 0.25;
		float node_mut_prob = 0.05;

		int curr_gen_num = 0;
		
		// Return average fitness of initial pop
		float initialize_pop(int grid_size);
		ParseGraph* selection(int tournament_size);
		void crossover(ParseGraph* g1, ParseGraph* g2);
		void global_mutation(ParseGraph* g);
		void link_mutation(ParseGraph* g);
		void node_mutation(ParseGraph* g);
		// Return average fitness at end
		float eval_fitness();
		float next_gen();
		float run(bool verbose);
	private:
		vector<ParseGraph*> tmp_pop;
};

#endif

