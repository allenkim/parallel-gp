#include <cstdlib>
#include <ctime>
#include "random.h"

void init_rand_state(int num_threads, int seed){
	if (seed == -1)
		srand(time(NULL));
	else
		srand(seed);
	state = new unsigned int[num_threads*4];
	for (int i = 0; i < num_threads*4; i++){
		state[i] = i * 5039 + 479001597 + rand() % 39916801;
	}
}

unsigned int xorshift128(unsigned int* state, unsigned int size){
	/* Algorithm "xor128" from p. 5 of Marsaglia, "Xorshift RNGs" */
	unsigned int s, t = state[3];
	t ^= t << 11;
	t ^= t >> 8;
	state[3] = state[2]; state[2] = state[1]; state[1] = s = state[0];
	t ^= s;
	t ^= s >> 19;
	state[0] = t;
	return t;
}

unsigned int rand(int id){
	return xorshift128(state+id*4,4);
}

float randf(int id){
	return (float)rand(id) / 4294967296;
}
