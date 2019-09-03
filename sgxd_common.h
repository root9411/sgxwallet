//
// Created by kladko on 9/3/19.
//

#ifndef SGXD_SGXD_COMMON_H
#define SGXD_SGXD_COMMON_H

#include <stdbool.h>

#define BUF_LEN 1024

#define  MAX_KEY_LENGTH 128
#define  MAX_COMPONENT_LENGTH 80
#define  MAX_COMPONENT_HEX_LENGTH MAX_COMPONENT_LENGTH * 2
#define  MAX_ENCRYPTED_KEY_LENGTH 1024
#define  MAX_SIG_LEN 1024
#define  MAX_ERR_LEN 1024
#define SHA_256_LEN 32

#define ADD_ENTROPY_SIZE 32

inline int char2int(char _input) {
    if (_input >= '0' && _input <= '9')
        return _input - '0';
    if (_input >= 'A' && _input <= 'F')
        return _input - 'A' + 10;
    if (_input >= 'a' && _input <= 'f')
        return _input - 'a' + 10;
    return -1;
}



void carray2Hex(const unsigned char *d, int _len, char* _hexArray) {

    static char hexval[16] = {'0', '1', '2', '3', '4', '5', '6', '7',
                              '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

    for (int j = 0; j < _len; j++) {
        _hexArray[j * 2] = hexval[((d[j] >> 4) & 0xF)];
        _hexArray[j * 2 + 1] = hexval[(d[j]) & 0x0F];
    }

    _hexArray[_len * 2] = 0;

}


bool hex2carray(const char * _hex, uint64_t  *_bin_len,
    uint8_t* _bin ) {

    int len = strnlen(_hex, 2 * BUF_LEN);


    if (len == 0 && len % 2 == 1)
        return false;

    *_bin_len = len / 2;

    for (int i = 0; i < len / 2; i++) {
        int high = char2int((char)_hex[i * 2]);
        int low = char2int((char)_hex[i * 2 + 1]);

        if (high < 0 || low < 0) {
            return false;
        }

        _bin[i] = (unsigned char) (high * 16 + low);
    }

    return true;

}



#endif //SGXD_SGXD_COMMON_H