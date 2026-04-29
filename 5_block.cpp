#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>

using namespace std;

// SHA256 function
string sha256(const string &input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)input.c_str(), input.size(), hash);

    stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}

// Block class
class Block {
public:
    int index;
    string data;
    string previousHash;
    string hash;

    Block(int idx, string d, string prevHash) {
        index = idx;
        data = d;
        previousHash = prevHash;
        hash = calculateHash();
    }

    string calculateHash() {
        stringstream ss;
        ss << index << data << previousHash;
        return sha256(ss.str());
    }
};

// Blockchain class
class Blockchain {
public:
    vector<Block> chain;

    Blockchain() {
        chain.push_back(Block(0, "Genesis Block", "0"));
    }

    void addBlock(string data) {
        Block prev = chain.back();
        Block newBlock(chain.size(), data, prev.hash);
        chain.push_back(newBlock);
    }

    void displayChain() {
        cout << "\n========== BLOCKCHAIN ==========\n";
        for (const auto &block : chain) {
            cout << "Block Index      : " << block.index << endl;
            cout << "Data             : " << block.data << endl;
            cout << "Previous Hash    : " << block.previousHash << endl;
            cout << "Current Hash     : " << block.hash << endl;
            cout << "----------------------------------------\n";
        }
    }

    bool isValid() {
        for (size_t i = 1; i < chain.size(); i++) {
            Block current = chain[i];
            Block previous = chain[i - 1];

            // Check hash correctness
            if (current.hash != current.calculateHash()) {
                cout << "? Hash mismatch at Block " << current.index << endl;
                return false;
            }

            // Check linking
            if (current.previousHash != previous.hash) {
                cout << "? Chain broken between Block "
                     << previous.index << " and Block " << current.index << endl;
                return false;
            }
        }
        return true;
    }

    void tamperBlock(int index, string newData) {
        cout << "\n?? Tampering Block " << index << "...\n";
        chain[index].data = newData;
        chain[index].hash = chain[index].calculateHash(); // update its hash only
    }
};

// MAIN
int main() {
    Blockchain bc;

    // Create 5 blocks
    bc.addBlock("A -> B");
    bc.addBlock("B -> C");
    bc.addBlock("C -> D");
    bc.addBlock("D -> E");

    cout << "\n? ORIGINAL BLOCKCHAIN\n";
    bc.displayChain();

    // Validate before tampering
    cout << "\n?? Checking Integrity...\n";
    if (bc.isValid()) {
        cout << "? Blockchain is VALID\n";
    } else {
        cout << "? Blockchain is INVALID\n";
    }

    // Tamper 3rd block (index 2)
    bc.tamperBlock(2, "HACKED DATA");

    cout << "\n?? BLOCKCHAIN AFTER TAMPERING\n";
    bc.displayChain();

    // Validate after tampering
    cout << "\n?? Checking Integrity Again...\n";
    if (bc.isValid()) {
        cout << "? Blockchain is VALID\n";
    } else {
        cout << "? Blockchain is INVALID (Tampering detected!)\n";
    }

    return 0;
}
