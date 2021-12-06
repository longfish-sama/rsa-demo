#include "Untitled-1.hpp"
#include "cppcodec-0.2/cppcodec/hex_default_lower.hpp"
using namespace std;
using namespace cppcodec;

int main()
{
    mpz_t p, q, n, e, d, phi;
    mpz_init_set_str(p, "0", HEX_BASE);
    mpz_init_set_str(q, "0", HEX_BASE);
    mpz_init(n);
    mpz_init(d);
    mpz_init(phi);
    mpz_init_set_ui(e, 65537);
    //生成两个大质数pq
    while (!mpz_cmp(p, q))
    {
        genPrime(p, q);
    }
    //计算n
    mpz_mul(n, p, q);
    //计算d
    calD(d, p, q, e);
    gmp_printf("p:\n%Zx\n", p);
    cout << "length p = " << mpz_sizeinbase(p, BIN_BASE) << " bits" << endl;
    gmp_printf("q:\n%Zx\n", q);
    cout << "length q = " << mpz_sizeinbase(q, BIN_BASE) << " bits" << endl;
    gmp_printf("d:\n%Zx\n", d);
    cout << "length d = " << mpz_sizeinbase(d, BIN_BASE) << " bits" << endl;
    gmp_printf("n:\n%Zx\n", n);
    cout << "length n = " << mpz_sizeinbase(n, BIN_BASE) << " bits" << endl;
    string s = "abcdefg";
    string ss = hex_lower::encode(s.data(),s.length());
    string en = encryptPKey(ss, n, e);
    string de = decryptSKey(en, n, d);
    char *re = new char[de.length()+16];
    hex_lower::decode(re,de.length(),de.data(),de.length());

    return 0;
}