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
    string sha256(string value);
};