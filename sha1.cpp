#include <iostream>
#include <openssl/sha.h>
#include <iomanip>
#include <sstream>

using namespace std;

int main() {
    string message = " Blockchain Developer";
    unsigned char hash[SHA_DIGEST_LENGTH];

    SHA1((unsigned char*)message.c_str(), message.length(), hash);

    cout << "Message: \"" << message << "\"" << endl;
    cout << "SHA-1 Digest: ";

    for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
        cout << hex << setw(2) << setfill('0') << (int)hash[i];
    }

    cout << endl;
    return 0;
}
