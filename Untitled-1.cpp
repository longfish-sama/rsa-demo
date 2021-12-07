#include "Untitled-1.hpp"
#include "src/cppcodec-0.2/cppcodec/hex_default_lower.hpp"
#include "src/clipp.h"
#include <fstream>
#define GEN_KEY_MODE 0
#define ENCRYPT_MODE 1
#define DECRYPT_MODE 2
using namespace std;

int main(int argc, char *argv[])
{
    string plain_text = "";
    string cipher_text = "";
    int mode = 0;
/*
    auto cli = ((clipp::required("-g", "--genkey").set(mode, GEN_KEY_MODE) % "generate random key pair") |
                ((clipp::required("-e", "--encrypt").set(mode, ENCRYPT_MODE) & clipp::value("string", plain_text)) % "encrypt string") |
                ((clipp::required("-d", "--decrypt").set(mode, DECRYPT_MODE) & clipp::value("string", cipher_text)) % "decrypt string"));
    if (!clipp::parse(argc, argv, cli))
    {
        cout << clipp::make_man_page(cli, argv[0]) << endl;
        return 1;
    }
*/
    if (mode == GEN_KEY_MODE)
    {
        //生成随机密钥对
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

        ofstream public_key("publicKey", ios::out);
        if (!public_key.is_open())
        {
            cout << "write file \"publicKey\" error" << endl;
            return 1;
        }
        char *tmp_char = new char[LEN];
        public_key << mpz_get_str(tmp_char, HEX_BASE, e) << endl;
        public_key<<mpz_get_str(tmp_char,HEX_BASE,n)<<endl;
        public_key.close();
        
    }
    else if (mode == ENCRYPT_MODE)
    {
    }
    else if (mode == DECRYPT_MODE)
    {
    }
    else
    {
        //cout << clipp::make_man_page(cli, argv[0]) << endl;
        return 1;
    }
    string s = "abcdefgichimokuren";
    string ss = cppcodec::hex_lower::encode(s.data(), s.length() + 1); //包含字符串结束符
    const char *t = s.data();
    //string en = encryptPKey(ss, n, e);
    //string de = decryptSKey(en, n, d);
    //char *re = new char[de.length() + 1];
    //cppcodec::hex_lower::decode(re, de.length() + 1, de.data(), de.length() + 1);

    return 0;
}