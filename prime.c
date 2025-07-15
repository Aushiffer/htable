#include "prime.h"

char is_prime(const int n) {
    if (n < 2)
        return 2;

    // Must be 2 or 3
    if (n < 4)
        return 1;

    if (n % 2 == 0)
        return 0;

    for (int i = 3; i < floor(sqrt((double)n)); i += 2) {
        if (n % i == 0)
            return 0;
    }
    
    return 1;
}

int next_prime(int n) {
    while (is_prime(n) != 1)
        n++;

    return n;
}