#include <iostream>
#include <random>
#include "Init_vec.hpp"

unsigned long long InitClass::generateRandomNumber() {
    // �����G���W���̐���
    std::random_device rd;
    std::mt19937_64 gen(rd());
    
    // 16���̃����_���Ȑ����𐶐�
    std::uniform_int_distribution<unsigned long long> dist(1000000000000000ULL, 9999999999999999ULL);
    return dist(gen);
}

std::string InitClass::generateCommonKey() {
    // �����G���W���̐���
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // 16���̃����_���ȕ�����𐶐�
    const std::string charset = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::uniform_int_distribution<std::size_t> dist(0, charset.size() - 1);
    
    std::string result;
    for (int i = 0; i < 16; ++i) {
        result += charset[dist(gen)];
    }
    
    return result;
}