#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include <sstream>
#include <iomanip>

using namespace std;

// HASH FUNCTION 
string simpleHash(string input) {
    hash<string> h;
    return to_string(h(input));
}

// TRANSACTION 
struct Transaction {
    string sender;
    string receiver;
    double amount;
};

// BLOCK
class Block {
public:
    int index;
    string previousHash;
    string currentHash;
    vector<Transaction> transactions;
    string timestamp;

    Block(int idx, vector<Transaction> txs, string prevHash) {
        index = idx;
        transactions = txs;
        previousHash = prevHash;
        timestamp = getTime();
        currentHash = calculateHash();
    }

    string getTime() {
        time_t now = time(0);
        string t = ctime(&now);
        t.pop_back(); // remove newline
        return t;
    }

    string calculateHash() {
        stringstream ss;
        ss << index << previousHash << timestamp;
        for (auto &tx : transactions) {
            ss << tx.sender << tx.receiver << tx.amount;
        }
        return simpleHash(ss.str());
    }

    void display() {
        cout << "\n===== BLOCK " << index << " =====\n";
        cout << "Timestamp      : " << timestamp << endl;
        cout << "Previous Hash  : " << previousHash << endl;
        cout << "Current Hash   : " << currentHash << endl;

        cout << "Transactions:\n";
        for (auto &tx : transactions) {
            cout << "  " << tx.sender << " -> " 
                 << tx.receiver << " : " << tx.amount << endl;
        }
    }
};

// BLOCKCHAIN 
class Blockchain {
private:
    vector<Block> chain;
    map<string, double> balance;
    vector<Transaction> pendingTx;

public:
    Blockchain() {
        chain.push_back(Block(0, {}, "0")); // Genesis block
    }

    string getLastHash() {
        return chain.back().currentHash;
    }

    // Add transaction (pending)
    void addTransaction(string sender, string receiver, double amount) {

        if (sender != "SYSTEM" && balance[sender] < amount) {
            cout << "? Insufficient Balance!\n";
            return;
        }

        pendingTx.push_back({sender, receiver, amount});
        cout << "? Transaction added to pending list.\n";
    }

    // Mine block (add block to chain)
    void mineBlock() {
        if (pendingTx.empty()) {
            cout << "? No transactions to mine.\n";
            return;
        }

        // Update balances
        for (auto &tx : pendingTx) {
            if (tx.sender != "SYSTEM")
                balance[tx.sender] -= tx.amount;

            balance[tx.receiver] += tx.amount;
        }

        Block newBlock(chain.size(), pendingTx, getLastHash());
        chain.push_back(newBlock);

        pendingTx.clear();

        cout << "? Block mined successfully!\n";
    }

    void showBlockchain() {
        for (auto &block : chain) {
            block.display();
        }
    }

    void checkBalance(string user) {
        cout << "?? Balance of " << user << " = " << balance[user] << endl;
    }

    // Validate blockchain
    void validateChain() {
        for (int i = 1; i < chain.size(); i++) {
            if (chain[i].previousHash != chain[i - 1].currentHash) {
                cout << "? Blockchain is INVALID!\n";
                return;
            }
        }
        cout << "? Blockchain is VALID.\n";
    }
};

int main() {
    Blockchain bc;
    int choice;
    string sender, receiver;
    double amount;

    while (true) {
        cout << "\n====== MENU ======\n";
        cout << "1. Add Transaction\n";
        cout << "2. Mine Block\n";
        cout << "3. Check Balance\n";
        cout << "4. View Blockchain\n";
        cout << "5. Validate Blockchain\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Sender (or SYSTEM): ";
            cin >> sender;
            cout << "Receiver: ";
            cin >> receiver;
            cout << "Amount: ";
            cin >> amount;
            bc.addTransaction(sender, receiver, amount);
            break;

        case 2:
            bc.mineBlock();
            break;

        case 3:
            cout << "Enter user: ";
            cin >> sender;
            bc.checkBalance(sender);
            break;

        case 4:
            bc.showBlockchain();
            break;

        case 5:
            bc.validateChain();
            break;

        case 6:
            return 0;

        default:
            cout << "Invalid choice!\n";
        }
    }
}
