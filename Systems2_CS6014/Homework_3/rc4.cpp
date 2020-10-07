//
// Created by Derek Olson on 2/26/20.


#include "rc4.h"
#include "Key.h"

rc4::rc4(std::string password) {
    Key key = Key(password);
    int length = password.size();

    for(int k = 0; k < 256; k++){
        s[k]=k;
    }

    j = 0;

    for(i = 0; i < 256 ; i++){
        j=(j + s[i] + key.key[i % length]) % 256;
        swap(i, j);
    }

    i = 0;
    j = 0;
}

void rc4::swap(int a, int b){
    uint8_t temp = s[i];
    s[i] = s[j];
    s[j] = temp;
}

uint8_t rc4::genNextByte(){
    i = (i + 1) % 256;
    j = (j + s[i]) % 256;
    swap(i, j);
    int index=(s[i] +s [j]) % 256;
    return s[index];
}