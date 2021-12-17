# rsa-demo

a demo application of RSA Algorithm

RSA公钥密码算法的演示程序

## environment 环境

- Ubuntu 20.04

- gmp library (The GNU Multiple Precision Arithmetic Library)

## 使用

### 使用命令行输入

```
SYNOPSIS
        Untitled-1 (-g | (-e <plain text>) | (-d <cipher text>))

OPTIONS
        -g, --genkey
                    generate random key pair

        -e, --encrypt <plain text>
                    encrypt string

        -d, --decrypt <cipher text>
                    decrypt string
```

- generate random key pair

private key save as file "privateKey", public key save as file "publicKey", in HEX-base

### example 示例

- 随机生成密钥对 generate key pair

```
Untitled-1 -g
```

随机生成2048位的rsa密钥对，密钥文件privateKey与publicKey保存在程序目录下

- 加密字符串

```
Untitled-1 -e plainText
```

使用先前生成的公钥文件publicKey对"plainText"进行加密，输出加密后的串

- 解密串

```
Untitled-1 -d encrytped-string
```

使用先前生成的私钥文件privateKey对加密串进行解密（可从上一步的输出当中得到），输出解密后的串

## reference 参考

header [src/cppcodec](src/cppcodec) from tplgy/cppcodec <https://github.com/tplgy/cppcodec>

header [src/clipp.h](src/clipp.h) from muellan/clipp <https://github.com/muellan/clipp>