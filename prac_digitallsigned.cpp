#include <iostream>
#include <openssl/rsa.h>
#include <openssl/sha.h>
#include <openssl/objects.h>
#include <cstring>
using namespace std;
int main() {
    RSA *r = RSA_generate_key(2048, RSA_F4, NULL, NULL);
    string msg = "Hello this is signed";

    unsigned char h[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)msg.c_str(), msg.length(), h);

    unsigned char sig[256];
    unsigned int len;

    RSA_sign(NID_sha256, h, SHA256_DIGEST_LENGTH, sig, &len, r);
    cout << "Original Message: " << msg << endl;

    int v1 = RSA_verify(NID_sha256, h, SHA256_DIGEST_LENGTH, sig, len, r);

    if (v1 == 1)
        cout << "Valid signature (original message)" << endl;
    else
        cout << "Invalid signature (original message)" << endl;

    string msg2 = "Hello this is hacked";

    unsigned char h2[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)msg2.c_str(), msg2.length(), h2);
    int v2 = RSA_verify(NID_sha256, h2, SHA256_DIGEST_LENGTH, sig, len, r);

    cout << "Modified Message: " << msg2 << endl;

    if (v2 == 1)
        cout << "Valid signature (modified message)" << endl;
    else
        cout << "Invalid signature (modified message)" << endl;

    RSA_free(r);
    return 0;
    
    
    
    
}
