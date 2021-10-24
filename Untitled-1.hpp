#include <gmp.h>
#include <ctime>
#include <iostream>
using namespace std;

void genPrime(mpz_t return_prime)
{
    //声明及初始化变量
    mpz_t p;
    mpz_init(p);
    //生成随机数
    gmp_randstate_t rand_state;
    gmp_randinit_default(rand_state);
    gmp_randseed_ui(rand_state, time(NULL));
    mpz_urandomb(p, rand_state, 1024);
    //生成比p大的下一个素数
    mpz_nextprime(return_prime, p);
    mpz_clear(p);
}

void genD(mpz_t return_d, mpz_t p, mpz_t q, mpz_t e)
{
    //初始化
    mpz_t d, phi;
    mpz_init(d);
    mpz_init(phi);
    //计算欧拉函数phi
    mpz_sub_ui(p, p, 1);
    mpz_sub_ui(q, q, 1);
    mpz_mul(phi, p, q);
    //计算d
    mpz_invert(d, e, phi);
    return_d = d;
}