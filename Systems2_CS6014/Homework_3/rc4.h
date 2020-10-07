//
// Created by Derek Olson on 2/26/20.
//

#ifndef HOMEWORK_3_RC4_H
#define HOMEWORK_3_RC4_H

#include <cstdint>
#include <string>

class rc4{
public:
    int i, j;
    uint8_t s[256];

public:
    rc4(std::string password);
    void swap(int a, int b);
    uint8_t genNextByte();
};

#endif //HOMEWORK_3_RC4_H
