#include <iostream>
#include <openssl/md5.h>
#include <iomanip>

using namespace std;

int main() {
    string msg = "Hello World";
    unsigned char hash[MD5_DIGEST_LENGTH];

    MD5((unsigned char*)msg.c_str(), msg.length(), hash);

    cout << "Message : " << msg << endl;
    cout << "MD5     : ";

    for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
        cout << hex << setw(2) << setfill('0') << (int)hash[i];

    cout << endl;
    cout << "Decryption : Not possible (MD5 is one-way)" << endl;

    return 0;
}



