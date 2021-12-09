#include <gmp.h>
#include <ctime>
#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#define HEX_BASE 16
#define BIN_BASE 2
#define LEN 2048
using namespace std;

void genPrime(mpz_t &return_p, mpz_t &return_q)
{ //生成两个质数
    //声明及初始化变量
    mpz_t p, q;
    mpz_init(p);
    mpz_init(q);
    //生成随机数
    gmp_randstate_t rand_state;
    gmp_randinit_default(rand_state);
    gmp_randseed_ui(rand_state, time(NULL));
    mpz_urandomb(p, rand_state, LEN / 2);
    mpz_urandomb(q, rand_state, LEN / 2);
    //生成比p大的下一个素数
    mpz_nextprime(return_p, p);
    mpz_nextprime(return_q, q);
    mpz_clear(p);
    mpz_clear(q);
}

void calD(mpz_t &return_d, mpz_t &p, mpz_t &q, mpz_t &e)
{ //计算d
    //初始化
    mpz_t phi, p1, q1;
    mpz_init(phi);
    mpz_init(p1);
    mpz_init(q1);
    //计算欧拉函数phi
    mpz_sub_ui(p1, p, 1);
    mpz_sub_ui(q1, q, 1);
    mpz_mul(phi, p1, q1);
    //计算d
    mpz_invert(return_d, e, phi);
    mpz_clear(phi);
    mpz_clear(p1);
    mpz_clear(q1);
}

string encryptPKey(string &plain_text, mpz_t &n, mpz_t &e)
{ //使用公钥加密
    mpz_t M, C;
    mpz_init_set_str(M, plain_text.data(), HEX_BASE);
    mpz_init_set_ui(C, 0);
    //计算密文
    mpz_powm(C, M, e, n);
    char *encrypted_str = new char[plain_text.length() + 16];
    string return_str;
    mpz_get_str(encrypted_str, HEX_BASE, C);
    return_str = encrypted_str;
    return return_str;
}


string decryptSKey(string &cipher_text, mpz_t &n, mpz_t &d)
{
    mpz_t M, C;
    mpz_init_set_str(C, cipher_text.data(), HEX_BASE);
    mpz_init_set_ui(M, 0);
    //
    mpz_powm(M, C, d, n);
    char *decrypted_str = new char[cipher_text.length() + 16];
    string return_str;
    mpz_get_str(decrypted_str, HEX_BASE, M);
    return_str = decrypted_str;
    mpz_clear(M);
    mpz_clear(C);
    return return_str;
}