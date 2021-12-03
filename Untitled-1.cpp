#include "Untitled-1.hpp"
using namespace std;

int main()
{
    mpz_t p,q,n,e,d,phi;
    mpz_init_set_str(p,"0",2);
    mpz_init_set_str(q,"0",2);
    mpz_init(n);
    mpz_init(d);
    mpz_init(phi);
    mpz_init_set_ui(e, 65537);
    //生成两个大质数
    while (!mpz_cmp(p,q))
    {
        genPrime(p,q);
    }
    gmp_printf("p:\n%Zx\n", p);
    gmp_printf("q:\n%Zx\n", q);
    //计算d
    calD(d, p, q, e);
    gmp_printf("d:\n%Zd\n", d);
    //计算n
    mpz_mul(n,p,q);
    gmp_printf("n:\n%Zd\n", n);

    return 0;
}