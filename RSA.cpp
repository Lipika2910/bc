#include <iostream>
using namespace std;

// Fast Modular Exponentiation
long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;

    cout << "\n   Modular Exponentiation Steps:\n";
    while (exp > 0) {
        cout << "   base = " << base << ", exp = " << exp << ", result = " << result << endl;

        if (exp % 2 == 1) {
            result = (result * base) % mod;
            cout << "   -> result = (result * base) % mod = " << result << endl;
        }

        base = (base * base) % mod;
        exp = exp / 2;
    }
    return result;
}

// GCD Function
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Modular Inverse (Brute Force with steps)
int modInverse(int e, int phi) {
    cout << "\nFinding d such that (d * e) % phi = 1\n";   
    for (int d = 1; d < phi; d++) {
        cout << "Trying d = " << d << " -> (" << d << " * " << e << ") % " << phi 
             << " = " << (d * e) % phi << endl;

        if ((d * e) % phi == 1) {
            cout << "? Found d = " << d << endl;
            return d;
        }
    }
    return -1;
}

int main() {
    int p = 17, q = 11;
    int e = 7;
    int M = 8;

    cout << "================ RSA ALGORITHM ================\n";

    // Step 1
    cout << "\n[1] Given Values:\n";
    cout << "   p = " << p << ", q = " << q << ", e = " << e << ", M = " << M << endl;

    // Step 2
    int n = p * q;
    int phi = (p - 1) * (q - 1);

    cout << "\n[2] Calculate n and phi(n):\n";
    cout << "   n = p * q = " << p << " * " << q << " = " << n << endl;
    cout << "   phi(n) = (p-1)*(q-1) = " << (p-1) << " * " << (q-1) << " = " << phi << endl;

    // Step 3
    if (gcd(e, phi) != 1) {
        cout << "? e is not valid (not coprime with phi)\n";
        return 0;
    }

    int d = modInverse(e, phi);

    cout << "\n[3] Keys:\n";
    cout << "   Public Key (e, n) = (" << e << ", " << n << ")\n";
    cout << "   Private Key (d, n) = (" << d << ", " << n << ")\n";

    // Step 4 Encryption
    cout << "\n[4] Encryption:\n";
    cout << "   Formula: C = M^e mod n\n";
    cout << "   C = " << M << "^" << e << " mod " << n << endl;

    int C = modExp(M, e, n);
    cout << "   ? Ciphertext C = " << C << endl;

    // Step 5 Decryption
    cout << "\n[5] Decryption:\n";
    cout << "   Formula: M = C^d mod n\n";
    cout << "   M = " << C << "^" << d << " mod " << n << endl;

    int decrypted = modExp(C, d, n);
    cout << "   ? Decrypted Message = " << decrypted << endl;

    cout << "\n==============================================\n";

    return 0;
}
