//
// Created by Derek Olson on 2/24/20.
//

#ifndef HOMEWORK_3_KEY_H
#define HOMEWORK_3_KEY_H


class Key {
public:
    std::string password;
    uint8_t key[8];
public:
    Key(std::string password);
    const std::string &getPassword() const;
    const uint8_t *getKey() const;
};


#endif //HOMEWORK_3_KEY_H
