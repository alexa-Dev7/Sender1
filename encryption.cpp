#include "encryption.h"
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/aes.h>

string encryptMessage(const string &message) {
    // Simulated encryption (Replace with real AES encryption)
    return "ENC(" + message + ")";
}

string decryptMessage(const string &encrypted) {
    // Simulated decryption (Replace with real AES decryption)
    return encrypted.substr(4, encrypted.size() - 5);
}
