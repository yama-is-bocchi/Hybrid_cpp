#include <iostream>
#include <random>
#include <string>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#include <openssl/aes.h>
#include "Init_vec.hpp"
#include "AES.hpp"
//g++ -o AES.exe AES.cpp Init_vec.cpp -I"C:\Program Files\OpenSSL-Win64\include" -L"C:\Program Files\OpenSSL-Win64\lib\VC\x64\MTd" -lssl -lcrypto -Wno-deprecated-declarations


using namespace std;

// AES�Í����֐�
string AESClass::aesEncrypt(string plaintext, string key,string iv) {
    
    string ciphertext;

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

    // ������
    if (!EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, (const unsigned char*)key.c_str(), (const unsigned char*)iv.c_str())) {
        cout << "�Í����̏������Ɏ��s���܂���" << endl;
        return "";
    }

    // �Í�������K�v������o�b�t�@�̃T�C�Y���擾
    int ciphertext_len = plaintext.length() + AES_BLOCK_SIZE;
    unsigned char* encrypted = new unsigned char[ciphertext_len];

    int len;

    // �Í���
    if (!EVP_EncryptUpdate(ctx, encrypted, &len, (const unsigned char*)plaintext.c_str(), plaintext.length())) {
        cout << "�Í����Ɏ��s���܂���" << endl;
        return "";
    }

    // �t�@�C�i���C�Y
    int final_len;
    if (!EVP_EncryptFinal_ex(ctx, encrypted + len, &final_len)) {
        cout << "�Í����̃t�@�C�i���C�Y�Ɏ��s���܂���" << endl;
        return "";
    }
    len += final_len;

    // �Í����𕶎���ɕϊ�
    ciphertext.assign((char*)encrypted, len);

    delete[] encrypted;
    EVP_CIPHER_CTX_free(ctx);

    return ciphertext;
}

// AES�������֐�
string AESClass::aesDecrypt(string ciphertext, string key,string iv) {
    string decryptedText;

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

    // ������
    if (!EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, (const unsigned char*)key.c_str(), (const unsigned char*)iv.c_str())) {
        cout << "�������̏������Ɏ��s���܂���" << endl;
        return "";
    }

    // ����������K�v������o�b�t�@�̃T�C�Y���擾
    int decrypted_len = ciphertext.length() + AES_BLOCK_SIZE;
    unsigned char* decrypted = new unsigned char[decrypted_len];

    int len;

    // ������
    if (!EVP_DecryptUpdate(ctx, decrypted, &len, (const unsigned char*)ciphertext.c_str(), ciphertext.length())) {
        cout << "�������Ɏ��s���܂���" << endl;
        return "";
    }
    int plaintext_len = len;

    // �t�@�C�i���C�Y
    int final_len;
    if (!EVP_DecryptFinal_ex(ctx, decrypted + len, &final_len)) {
        cout << "�������̃t�@�C�i���C�Y�Ɏ��s���܂���" << endl;
        return "";
    }
    plaintext_len += final_len;

    // �������𕶎���ɕϊ�
    decryptedText.assign((char*)decrypted, plaintext_len);

    delete[] decrypted;
    EVP_CIPHER_CTX_free(ctx);

    return decryptedText;
}





