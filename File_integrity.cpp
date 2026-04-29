#include <iostream>
#include <openssl/sha.h>
#include <iomanip>
#include <fstream>

using namespace std;

int main() {
    unsigned char hash1[SHA256_DIGEST_LENGTH];
    unsigned char hash2[SHA256_DIGEST_LENGTH];

    ifstream file1("file1.txt", ios::binary);
    ifstream file2("file2.txt", ios::binary);

    SHA256_CTX ctx;

    SHA256_Init(&ctx);
    char ch;
    while (file1.get(ch)) {
        SHA256_Update(&ctx, &ch, 1);
    }
    SHA256_Final(hash1, &ctx);

    SHA256_Init(&ctx);
    while (file2.get(ch)) {
        SHA256_Update(&ctx, &ch, 1);
    }
    SHA256_Final(hash2, &ctx);

    cout << "Hash of file1.txt: ";
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        cout << hex << setw(2) << setfill('0') << (int)hash1[i];
    cout << endl;

    cout << "Hash of file2.txt: ";
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        cout << hex << setw(2) << setfill('0') << (int)hash2[i];
    cout << endl;

    if (memcmp(hash1, hash2, SHA256_DIGEST_LENGTH) == 0)
        cout << "File Integrity Verified" << endl;
    else
        cout << "File Integrity Compromised" << endl;

    return 0;
}
