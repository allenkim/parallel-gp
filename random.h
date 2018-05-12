#ifndef __RANDOM_H__
#define __RANDOM_H__

extern unsigned int* state;

void init_rand_state(int num_threads, int seed = -1);
unsigned int xorshift128(unsigned int* state, unsigned int size);
unsigned int rand(int id);
float randf(int id);

#endif
