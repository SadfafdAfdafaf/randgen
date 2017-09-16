#ifndef MYRAND
#define MYRAND

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define max(a,b) (((a)>(b))?(a):(b))

int LCM(int Xn, int k);
void GRA(int *res, int size); //based on LCM
void ICG(int n, int a, int c, int seed, int count, int* res);
void SICG(int n, int a, int c, int seed, int count, int p1, int p2, int* res);
unsigned long MWC(void);
unsigned long xor128(void); //Xorshift
int FWL(int level, int cas, int seed); //Fibonachi based om MWC, rand()

#endif 