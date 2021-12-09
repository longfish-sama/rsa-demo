#include "Untitled-1.hpp"
#include "src/cppcodec/hex_default_lower.hpp"
#include "src/clipp.h"
#define GEN_KEY_MODE 0
#define ENCRYPT_MODE 1
#define DECRYPT_MODE 2
#define PUBLIC_KEY_FILENAME "publicKey"
#define PRIVATE_KEY_FILENAME "privateKey"
using namespace std;

int main(int argc, char *argv[])
{
    string plain_text = "";
    string cipher_text = "";
    int mode = 0;
    auto cli = ((clipp::required("-g", "--genkey").set(mode, GEN_KEY_MODE) %
                 "generate random key pair") |
                ((clipp::required("-e", "--encrypt").set(mode, ENCRYPT_MODE) &
                  clipp::value("plain text", plain_text)) %
                 "encrypt string") |
                ((clipp::required("-d", "--decrypt").set(mode, DECRYPT_MODE) &
                  clipp::value("cipher text", cipher_text)) %
                 "decrypt string"));
    if (!clipp::parse(argc, argv, cli))
    {
        cout << clipp::make_man_page(cli, argv[0]) << endl;
        return 1;
    }

    if (mode == GEN_KEY_MODE)
    {
        //生成随机密钥对
        mpz_t p, q, n, e, d;
        mpz_init_set_str(p, "0", HEX_BASE);
        mpz_init_set_str(q, "0", HEX_BASE);
        mpz_init(n);
        mpz_init(d);
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
        cout << "length p: " << mpz_sizeinbase(p, BIN_BASE) << " bits" << endl;
        gmp_printf("q:\n%Zx\n", q);
        cout << "length q: " << mpz_sizeinbase(q, BIN_BASE) << " bits" << endl;
        gmp_printf("d:\n%Zx\n", d);
        cout << "length d: " << mpz_sizeinbase(d, BIN_BASE) << " bits" << endl;
        gmp_printf("n:\n%Zx\n", n);
        cout << "length n: " << mpz_sizeinbase(n, BIN_BASE) << " bits" << endl;

        //保存公钥
        ofstream public_key(PUBLIC_KEY_FILENAME, ios::out);
        if (!public_key.is_open())
        {
            cout << "write file \"" << PUBLIC_KEY_FILENAME << "\" error" << endl;
            return 1;
        }
        char *tmp_char = new char[LEN];
        public_key << mpz_get_str(tmp_char, HEX_BASE, e) << endl;
        public_key << mpz_get_str(tmp_char, HEX_BASE, n) << endl;
        public_key.close();
        //保存私钥
        ofstream private_key(PRIVATE_KEY_FILENAME, ios::out);
        if (!private_key.is_open())
        {
            cout << "write file \"" << PRIVATE_KEY_FILENAME << "\" error" << endl;
            return 1;
        }
        private_key << mpz_get_str(tmp_char, HEX_BASE, d) << endl;
        private_key << mpz_get_str(tmp_char, HEX_BASE, n) << endl;
        private_key.close();

        mpz_clear(p);
        mpz_clear(q);
        mpz_clear(n);
        mpz_clear(e);
        mpz_clear(d);
    }
    else if (mode == ENCRYPT_MODE)
    { //加密字符串
        //从文件读取公钥
        cout << "encrypt mode" << endl;
        ifstream public_key(PUBLIC_KEY_FILENAME);
        if (!public_key.is_open())
        {
            cout << "open file \"" << PUBLIC_KEY_FILENAME << "\" error" << endl;
            cout << clipp::make_man_page(cli, argv[0]) << endl;
            return 1;
        }
        string n_str, e_str;
        getline(public_key, e_str);
        getline(public_key, n_str);
        public_key.close();
        if (e_str.length() == 0 || n_str.length() == 0)
        {
            cout << "read key error" << endl;
            cout << clipp::make_man_page(cli, argv[0]) << endl;
            return 1;
        }
        cout << "n:\n"
             << n_str << endl;
        cout << "e:\n"
             << e_str << endl;
        //加密
        string base16_encode = "";
        string encrypted_str = "";
        mpz_t n, e;
        mpz_init_set_str(n, n_str.data(), HEX_BASE);
        mpz_init_set_str(e, e_str.data(), HEX_BASE);
        base16_encode = cppcodec::hex_lower::encode(plain_text.data(),
                                                    plain_text.length() + 1);
        encrypted_str = encryptPKey(base16_encode, n, e);
        cout << "plain text:\n"
             << plain_text << endl;
        cout << "base16 encode:\n"
             << base16_encode << endl;
        cout << "encrypted string:\n"
             << encrypted_str << endl;
        mpz_clear(n);
        mpz_clear(e);
    }
    else if (mode == DECRYPT_MODE)
    { //解密字符串
        //从文件读私钥
        cout << "decrypt mode" << endl;
        ifstream private_key(PRIVATE_KEY_FILENAME);
        if (!private_key.is_open())
        {
            cout << "open file \"" << PRIVATE_KEY_FILENAME << "\" error" << endl;
            cout << clipp::make_man_page(cli, argv[0]) << endl;
            return 1;
        }
        string n_str, d_str;
        getline(private_key, d_str);
        getline(private_key, n_str);
        if (d_str.length() == 0 || n_str.length() == 0)
        {
            cout << "read key error" << endl;
            cout << clipp::make_man_page(cli, argv[0]) << endl;
            return 1;
        }
        cout << "n:\n"
             << n_str << endl;
        cout << "d:\n"
             << d_str << endl;
        //解密
        mpz_t n, d;
        string decrypted_str;
        mpz_init_set_str(n, n_str.data(), HEX_BASE);
        mpz_init_set_str(d, d_str.data(), HEX_BASE);
        decrypted_str = decryptSKey(cipher_text, n, d);
        char *base16_decode = new char[decrypted_str.length() + 1];
        cppcodec::hex_lower::decode(base16_decode, decrypted_str.length() + 1,
                                    decrypted_str.data(), decrypted_str.length() + 1);
        cout << "decrypted string:\n"
             << base16_decode << endl;
        mpz_clear(n);
        mpz_clear(d);
    }
    else
    {
        cout << clipp::make_man_page(cli, argv[0]) << endl;
        return 1;
    }
    return 0;
}