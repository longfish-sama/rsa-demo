#include <gmp.h>
#include <iostream>
#include "Untitled-1.hpp"
using namespace std;

int main()
{
    mpz_t p, q, n,e,d,phi;
    mpz_init(p);
    mpz_init(q);
    mpz_init(n);
    genPrime(p);
    genPrime(q);
    gmp_printf("%Zx\n", p);
    gmp_printf("%Zx\n",q);
    while (p == q)
    {
        genPrime(q);
    }

    return 0;
}