#include <iostream>
#include <iomanip>
#include <sstream>
#include <openssl/sha.h>

using namespace std;

string sha256(string input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];

    SHA256((unsigned char*)input.c_str(), input.size(), hash);

    stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }

    return ss.str();
}

int main() {
    string input;

    cout << "Enter string: ";
    getline(cin, input);

    cout << "SHA-256 Hash: " << sha256(input) << endl;

    return 0;
}





