#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <iostream>
#include <string>
#include "Init_vec.hpp"
#include "AES.hpp"
#include "RSA.hpp"

//g++ -o Hybrid.exe Hybrid.cpp AES.cpp Init_vec.cpp RSA.cpp -I"C:\Program Files\OpenSSL-Win64\include" -L"C:\Program Files\OpenSSL-Win64\lib\VC\x64\MTd" -lssl -lcrypto -Wno-deprecated-declarations

using namespace std;

int main(){

    /*********************************************/
    /*******************���[�U�[A��****************/
    /*********************************************/

    //��,�������x�N�g�������N���X"Init_vec.hpp"
    InitClass init;
    //AES�Í����\�b�h�N���X"AES.hpp"
    AESClass AES;
    //RSA�Í����\�b�h�N���X"RSA.hpp"
    RSAClass rsaclass;
    
    // ������̓���
    string message ;
    cout << "\n���b�Z�[�W����͂��Ă�������: ";
    getline(cin,  message);

    //���ʌ��𐶐�
    string commonkey = init.generateCommonKey();
    cout << "\n���ʌ�: " << commonkey << endl;

    //�������x�N�g���𐶐�
    string  iv=to_string(init.generateRandomNumber());
    cout << "\n�������x�N�g��: " << iv << endl;
    
    //���ʌ��Ń��b�Z�[�W���Í���
    string encryptedMessage = AES.aesEncrypt(message, commonkey,iv);
    if (encryptedMessage.empty()) {
       cout << "\nAES�Í����Ɏ��s���܂���" << endl;
        return 1;
    }
    cout << "\n�Í������ꂽ���b�Z�[�W: " << encryptedMessage << endl;

    //���J��,�閧���𐶐�
    //�L�[�y�A�̐���
    RSA* rsa = rsaclass.createRSAKeyPair();
    if (rsa == NULL) {
        return -1;
    }
    string publicKey = rsaclass.getPublicKey(rsa);
    string privateKey = rsaclass.getPrivateKey(rsa);
    cout << "\n���J��:\n" << publicKey << endl;
    cout << "�閧��:\n" << privateKey << endl;

    //���J���ŋ��ʌ�,�������x�N�g�����Í���
    //���ʌ����Í���
    string encryptedcommonkey = rsaclass.encryptMessage(rsa, commonkey);
    cout << "\n�Í������ꂽ���ʌ�:\n-----BEGIN ENCRYPTED STRING-----\n" << encryptedcommonkey <<"\n-----END ENCRYPTED STRING-----\n"<< endl;
    //�������x�N�g�����Í���
    string encryptediv = rsaclass.encryptMessage(rsa, iv);
    cout << "\n�Í������ꂽ�������x�N�g��:\n-----BEGIN ENCRYPTED STRING-----\n" << encryptediv <<"\n-----END ENCRYPTED STRING-----\n"<< endl;

    /*********************************************/
    /*********************************************/
    /*********************************************/



    /*********************************************/
    /*******************���[�U�[B��****************/
    /*********************************************/
    /*�󂯎�����:�閧��,�Í������ꂽ���ʌ�,�Í������ꂽ�������x�N�g��,�Í������ꂽ���b�Z�[�W*/
    /*encryptedcommonkey,encryptediv,encryptedMessage*/
    
    //�閧���ňÍ������ꂽ���ʌ�,�������x�N�g���𕜍�
    string decryptedcommonkey = rsaclass.decryptMessage(rsa, encryptedcommonkey);
    cout << "\n�������ꂽ���ʌ�: " << decryptedcommonkey << endl;
    string decryptediv = rsaclass.decryptMessage(rsa, encryptediv);
    cout << "\n�������ꂽ�������x�N�g��: " << decryptediv << endl;

    //�����������ʌ��ňÍ������ꂽ���b�Z�[�W�𕜍�
    string decryptedMessage = AES.aesDecrypt(encryptedMessage, decryptedcommonkey,decryptediv);
    if (decryptedMessage.empty()) {
        cout << "\nAES�����Ɏ��s���܂���" << endl;
        return 1;
    }
    cout << "\n�������ꂽ���b�Z�[�W: " << decryptedMessage << endl;

    /*********************************************/
    /*********************************************/
    /*********************************************/

}