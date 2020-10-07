//
// Created by Derek Olson on 2/24/20.
//

#include <string>
#include "Key.h"

Key::Key(std::string password)
{
    this->password = password;

    for(int i = 0; i < 8; i++){
        key[i] = 0;
    }
    for(int i = 0; i < password.size(); i++){
        key[i % 8] = key[i % 8] xor password[i];
    }
}

const std::string &Key::getPassword() const
{
    return password;
}

const uint8_t *Key::getKey() const
{
    return key;
}
