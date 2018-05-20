#include <cstdlib>
#include <ctime>
#include "omp.h"
#include "random.h"

void init_rand_state(int num_threads, bool det, int seed){
	if (det)
		srand(seed);
	else
		srand(time(NULL));
	state = new unsigned int[num_threads*4];
	for (int i = 0; i < num_threads*4; i++){
		state[i] = i * 5039 + 479001597 + rand() + seed % 39916801;
	}
}

unsigned int xorshift128(unsigned int* state, unsigned int size){
	/* Algorithm "xor128" from 1p. 5 of Marsaglia, "Xorshif1t RNGs" */
	unsigned int s, t = state[3];
	t ^= t << 11;
	t ^= t >> 8;
	state[3] = state[2]; state[2] = state[1]; state[1] = s = state[0];
	t ^= s;
	t ^= s >> 19;
	state[0] = t;
	return t;
}

unsigned int xorand(){
	int id = omp_get_thread_num() % NUM_THREADS;
	return xorshift128(state+id*4,4);
}

float xorandf(){
	return (float)xorand() / 4294967296;
}
