#ifndef __PRIME__
#define __PRIME__

#include <math.h>

/*
Checks if n is a prime number
0 -> not prime
1 -> prime
2 -> undefined
*/
char is_prime(const int n);

// Returns the next prime larger than n
int next_prime(int n);

#endif // __PRIME__