#include <iostream>
#include "Key.h"
#include "Tables.h"
#include "rc4.h"

std::string encrypt(std::string message, std::string password, Tables tables)
{
    Key key = Key(password);

    uint8_t m[message.size()];

    for(int i = 0; i < message.size(); i++){
        m[i] = message[i];
    }

    for(int i = 0; i < 16; i++) {
        for (int j = 0; j < message.size(); j++) {
            m[j] = m[j] xor key.key[j % 8];
            m[j] = tables.arrays[j % 8][m[j]];
        }
        uint8_t temp[message.size()];
        for(int k = 0; k < message.size(); k++){
            temp[k] = m[k] >> 7;
        }
        for(int l = 0; l < message.size(); l++){
            if(l == message.size()-1){
                m[l] = (m[l] << 1) | temp[0];
            }
            else {
                m[l] = (m[l] << 1 )| temp[l+1];
            }
        }
    }
    std::string encryptedString;
    for(int n = 0; n < message.size(); n++){
        encryptedString += m[n];
    }
    return encryptedString;
}

std::string decrypt(std::string encryptedMessage, std::string password, Tables tables){
    Key key = Key(password);
    uint8_t m[encryptedMessage.size()];

    for(int x = 0; x < encryptedMessage.size(); x++){
        m[x] = encryptedMessage[x];
    }

    for(int i = 0; i < 16; i++) {
        uint8_t temp[encryptedMessage.size()];
        for(int k = 0; k < encryptedMessage.size(); k++){
            temp[k] = m[k] << 7;
        }
        for (int j = 0; j < encryptedMessage.size(); j++) {
            if(j == 0){
                m[j] = (m[j] >> 1) | temp[encryptedMessage.size()-1];
            }
            else {
                m[j] = (m[j] >> 1 )| temp[j-1];
            }
        }

        for (int l = 0; l < encryptedMessage.size(); l++) {
            for(int o = 0; o < 256; o++){
                if(tables.arrays[l%8][o] == m[l]){
                    m[l] = o;
                    break;
                }
            }
        }
        for (int p = 0; p < encryptedMessage.size(); p++){
            m[p] = m[p] xor key.key[p % 8];
        }

    }
    std::string decryptedString;
    for(int n = 0; n < encryptedMessage.size(); n++){
        decryptedString += m[n];
    }
    return decryptedString;
}

std::string rc4Encrypt(std::string message, std::string password){

    uint8_t m[message.size()];
    for(int i = 0; i < message.size(); i++){
        m[i] = message[i];
    }

    std::string out;
    rc4 r = rc4(password);
    for(int i = 0; i < message.size(); i++){
        out += r.genNextByte() ^ m[i];
    }
    return out;
}


int main() {
    std::string message = "hello";
    Tables tables = Tables();
    std::string encrypted = encrypt(message, "passwords", tables);
    std::cout << encrypted << "\n";



    std::string decrypted = decrypt(encrypted, "passwords", tables);
    std::cout << decrypted << "\n";

//    std::string rc4Enc = rc4Encrypt("My salary is $1000", "password");
//    std::cout << rc4Enc << "\n";
//
//    std::string bitFlipped;
//    for(int i = rc4Enc.size() - 4; i < rc4Enc.size(); i++){
//        if(i == rc4Enc.size() - 4){
//            bitFlipped += rc4Enc[i] xor 0b1000;
//        }
//        else {
//            bitFlipped += rc4Enc[i] xor 0b1001;
//        }
//    }
//    std::cout << "bitFlipped: "+ bitFlipped << "\n";
//    bitFlipped = rc4Enc.substr(0, rc4Enc.size()-4) + bitFlipped;
//
//
//    std::string rc4DecBitFlipped = rc4Encrypt(bitFlipped, "password");
//    std::cout << rc4DecBitFlipped << "\n";
//
//    std::string rc4Dec = rc4Encrypt(rc4Enc, "password");
//    std::cout << rc4Dec << "\n";
//
//    //Verify that decrypting a message with a different key than the encryption key does not reveal the plaintext.
//    std::string rc4DecDiff = rc4Encrypt(rc4Enc, "passworl");
//    std::cout << rc4DecDiff << "\n";
//
//    //Verify that encrypting 2 messages using the same keystream is insecure (what do you expect to see if you xor the two encrypted messages?)
//    std::string rc4_1 = rc4Encrypt("test1", "password");
//    std::string rc4_2 = rc4Encrypt("test2", "password");
//
//    std::string out;
//    for(int i = 0; i < rc4_1.size(); i++){
//        out += rc4_1[i] xor rc4_2[i];
//    }
//    std::cout <<  out + "\n";

    return 0;
}
