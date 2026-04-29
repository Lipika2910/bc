#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

// Simple hash function (demo only)
string simpleHash(string input) {
    unsigned long hash = 5381;
    for (char c : input) {
        hash = ((hash << 5) + hash) + c;
    }

    stringstream ss;
    ss << hex << hash;
    return ss.str();
}

// Block Class
class Block {
public:
    int index;
    string data;
    string previousHash;
    string hash;
    int nonce;

    Block(int idx, string d, string prevHash) {
        index = idx;
        data = d;
        previousHash = prevHash;
        nonce = 0;
        hash = calculateHash();
    }

    string calculateHash() {
        stringstream ss;
        ss << index << data << previousHash << nonce;
        return simpleHash(ss.str());
    }

    void mineBlock(int difficulty) {
        string target(difficulty, '0');
        int maxAttempts = 50000;

        cout << "\n========================================\n";
        cout << "?? Mining Block " << index << endl;
        cout << "Target Condition : Hash starts with \"" << target << "\"\n";

        while (hash.substr(0, difficulty) != target && nonce < maxAttempts) {
            nonce++;
            hash = calculateHash();

            if (nonce % 5000 == 0) {
                cout << "Trying nonce: " << nonce 
                     << " | Hash: " << hash << endl;
            }
        }

        if (hash.substr(0, difficulty) == target) {
            cout << "? Block Mined Successfully!\n";
        } else {
            cout << "?? Stopped after max attempts\n";
        }

        cout << "Final Nonce : " << nonce << endl;
        cout << "Final Hash  : " << hash << endl;
        cout << "========================================\n";
    }
};

// Blockchain Class
class Blockchain {
public:
    vector<Block> chain;
    int difficulty;

    Blockchain() {
        difficulty = 1; // FAST & SAFE
        chain.push_back(createGenesisBlock());
    }

    Block createGenesisBlock() {
        cout << "?? Creating Genesis Block...\n";
        return Block(0, "Genesis Block", "0");
    }

    Block getLatestBlock() {
        return chain.back();
    }

    void addBlock(string data) {
        Block newBlock(chain.size(), data, getLatestBlock().hash);

        cout << "\n?? Adding Block " << newBlock.index;
        cout << "\nData: " << data << endl;
        cout << "Previous Hash: " << newBlock.previousHash << endl;

        newBlock.mineBlock(difficulty);
        chain.push_back(newBlock);
    }

    void printBlockchain() {
        cout << "\n\n========== FINAL BLOCKCHAIN ==========\n";

        for (auto &block : chain) {
            cout << "\n--------------------------------------\n";
            cout << "Index          : " << block.index << endl;
            cout << "Data           : " << block.data << endl;
            cout << "Previous Hash  : " << block.previousHash << endl;
            cout << "Hash           : " << block.hash << endl;
            cout << "Nonce          : " << block.nonce << endl;
        }

        cout << "\n======================================\n";
    }
};

int main() {
    cout << "?? SIMPLE BLOCKCHAIN (Proof of Work)\n";

    Blockchain myChain;

    myChain.addBlock("A -> B");
    myChain.addBlock("B -> C");
    myChain.addBlock("C -> D");

    myChain.printBlockchain();

    return 0;
}
