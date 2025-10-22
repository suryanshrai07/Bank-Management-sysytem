#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

class Customer {
    int accNo;
    string name;
    double balance;

public:
    Customer() {}
    Customer(int a, string n, double b) : accNo(a), name(n), balance(b) {}

    int getAccNo() { return accNo; }
    string getName() { return name; }
    double getBalance() { return balance; }

    void setName(string n) { name = n; }
    void setBalance(double b) { balance = b; }

    void show() {
        cout << setw(10) << accNo << setw(20) << name << setw(10) << balance << endl;
    }
};

// Function to load customers from file
vector<Customer> loadCustomers() {
    vector<Customer> list;
    ifstream fin("customers.txt");
    if (!fin) {
        // file does not exist yet, return empty list
        return list;
    }
    int a;
    string n;
    double b;
    while (fin >> a >> n >> b)
        list.push_back(Customer(a, n, b));
    fin.close();
    return list;
}

// Function to save customers to file
void saveCustomers(vector<Customer> &list) {
    ofstream fout("customers.txt");
    for (auto &c : list)
        fout << c.getAccNo() << " " << c.getName() << " " << c.getBalance() << endl;
    fout.close();
}

void createAccount(vector<Customer> &list) {
    int a;
    string n;
    double b;
    cout << "Enter Account No, Name, Initial Deposit: ";
    cin >> a >> n >> b;
    if (b < 0) {
        cout << "Initial deposit cannot be negative.\n";
        return;
    }
    for (auto &c : list) {
        if (c.getAccNo() == a) {
            cout << "Account number exists.\n";
            return;
        }
    }
    list.push_back(Customer(a, n, b));
    cout << "Account created\n";
    saveCustomers(list);  // Save immediately after creation
}

void deposit(vector<Customer> &list) {
    int a;
    double amount;
    cout << "Enter Account No: ";
    cin >> a;
    for (auto &c : list) {
        if (c.getAccNo() == a) {
            cout << "Enter Amount: ";
            cin >> amount;
            if (amount <= 0) {
                cout << "Invalid amount !!\n";
                return;
            }
            c.setBalance(c.getBalance() + amount);
            cout << "Deposit successful\n";
            saveCustomers(list);  // Save immediately after deposit
            return;
        }
    }
    cout << "Account not found\n";
}

void withdraw(vector<Customer> &list) {
    int a;
    double amount;
    cout << "Enter Account No: ";
    cin >> a;
    for (auto &c : list) {
        if (c.getAccNo() == a) {
            cout << "Enter Amount: ";
            cin >> amount;
            if (c.getBalance() < amount) {
                cout << "Insufficient balance\n";
                return;
            }
            c.setBalance(c.getBalance() - amount);
            cout << "Withdrawal successful\n";
            saveCustomers(list);  // Save after withdrawal
            return;
        }
    }
    cout << "Account not found\n";
}

void showAccount(vector<Customer> &list) {
    int a;
    cout << "Enter Account No: ";
    cin >> a;
    for (auto &c : list) {
        if (c.getAccNo() == a) {
            cout << "Account Details:\n";
            c.show();
            return;
        }
    }
    cout << "Account not found\n";
}

void showAll(vector<Customer> &list) {
    cout << setw(10) << "AccNo" << setw(20) << "Name" << setw(10) << "Balance" << endl;
    for (auto &c : list) c.show();
}

int main() {
    vector<Customer> customers = loadCustomers();
    int choice;
    do {
        cout << "\n*** Bank Management ***\n";
        cout << "1. Create Account\n2. Deposit\n3. Withdraw\n4. Show Account\n5. Show All Accounts\n6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: createAccount(customers); break;
            case 2: deposit(customers); break;
            case 3: withdraw(customers); break;
            case 4: showAccount(customers); break;
            case 5: showAll(customers); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice\n";
        }
    } while (choice != 6);
    return 0;
}
