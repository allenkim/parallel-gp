#ifndef __RANDOM_H__
#define __RANDOM_H__

extern unsigned int* state;
extern int NUM_THREADS;

void init_rand_state(int num_threads, bool det, int seed = 1);
unsigned int xorshift128(unsigned int* state, unsigned int size);
unsigned int xorand();
float xorandf();

#endif
