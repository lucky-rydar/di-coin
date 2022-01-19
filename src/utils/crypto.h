#pragma once
#include <string>
#include <sstream>
#include <iomanip>

#include <openssl/rsa.h>
#include <openssl/sha.h>

using namespace std;

namespace crypto
{
    // hashing
    const size_t sha256_size = 64;

    string sha256(string value);
};