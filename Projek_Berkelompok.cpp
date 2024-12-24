#include <iostream>
#include <iomanip>
#include <string>
#include <stack>
#include <queue>
using namespace std;

struct Account
{
    int accountNumber;
    string accountName;
    float balance;
};

struct AccountNode
{
    Account account;
    AccountNode *next;
};

struct GraphNode
{
    AccountNode *accountNode;
    GraphNode *next;
};

class Graph
{
private:
    GraphNode *head;

public:
    Graph()
    {
        head = nullptr;
    }

    void addNode(AccountNode *accountNode)
    {
        GraphNode *newNode = new GraphNode();
        newNode->accountNode = accountNode;
        newNode->next = nullptr;

        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            GraphNode *current = head;
            while (current->next != nullptr)
            {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    void displayGraph()
    {
        GraphNode *current = head;
        while (current != nullptr)
        {
            AccountNode *accountNode = current->accountNode;
            cout << "Account Number: " << accountNode->account.accountNumber << endl;
            cout << "Account Name: " << accountNode->account.accountName << endl;
            cout << "Balance: Rp. " << fixed << setprecision(2) << accountNode->account.balance << endl;
            cout << endl;

            current = current->next;
        }
    }

    ~Graph()
    {
        GraphNode *current = head;
        while (current != nullptr)
        {
            GraphNode *temp = current;
            current = current->next;
            delete temp;
        }
    }
};

class AccountList
{
private:
    AccountNode *head;
    stack<Account> accountStack;
    queue<Account> accountQueue;
    Graph accountGraph;

public:
    AccountList()
    {
        head = nullptr;
    }

    void createAccount(int accountNumber, string accountName, float balance)
    {
        AccountNode *newNode = new AccountNode();
        newNode->account.accountNumber = accountNumber;
        newNode->account.accountName = accountName;
        newNode->account.balance = balance;

        newNode->next = head;
        head = newNode;

        accountStack.push(newNode->account);
        accountQueue.push(newNode->account);

        accountGraph.addNode(newNode);

        cout << "Account created successfully!\n";
    }

    void displayAccounts()
    {
        cout << setw(15) << left << "Account No." << setw(20) << left << "Account Name" << setw(10) << left << "Balance" << endl;
        cout << setfill('-') << setw(45) << "-" << setfill(' ') << endl;

        AccountNode *current = head;
        while (current != nullptr)
        {
            Account currentAccount = current->account;
            cout << setw(15) << left << currentAccount.accountNumber << setw(20) << left << currentAccount.accountName << "Rp. " << setw(9) << right << fixed << setprecision(2) << currentAccount.balance << endl;

            current = current->next;
        }
    }

    void deposit(int accountNumber, float amount)
    {
        AccountNode *current = head;
        while (current != nullptr)
        {
            if (current->account.accountNumber == accountNumber)
            {
                current->account.balance += amount;
                cout << "Deposit successful! New balance: Rp. " << fixed << setprecision(2) << current->account.balance << endl;

                stack<Account> tempStack;
                queue<Account> tempQueue;
                while (!accountStack.empty())
                {
                    if (accountStack.top().accountNumber == accountNumber)
                    {
                        tempStack.push(current->account);
                    }
                    else
                    {
                        tempStack.push(accountStack.top());
                    }
                    accountStack.pop();
                }

                while (!accountQueue.empty())
                {
                    if (accountQueue.front().accountNumber == accountNumber)
                    {
                        tempQueue.push(current->account);
                    }
                    else
                    {
                        tempQueue.push(accountQueue.front());
                    }
                    accountQueue.pop();
                }

                while (!tempStack.empty())
                {
                    accountStack.push(tempStack.top());
                    tempStack.pop();
                }

                while (!tempQueue.empty())
                {
                    accountQueue.push(tempQueue.front());
                    tempQueue.pop();
                }

                return;
            }
            current = current->next;
        }

        cout << "Account not found. Please try again.\n";
    }

    void deleteAccount(int accountNumber)
    {
        AccountNode *current = head;
        AccountNode *prev = nullptr;
        while (current != nullptr)
        {
            if (current->account.accountNumber == accountNumber)
            {
                if (prev != nullptr)
                {
                    prev->next = current->next;
                }
                else
                {
                    head = current->next;
                }

                delete current;
                cout << "Account deleted successfully!\n";

                stack<Account> tempStack;
                queue<Account> tempQueue;
                while (!accountStack.empty())
                {
                    if (accountStack.top().accountNumber != accountNumber)
                    {
                        tempStack.push(accountStack.top());
                    }
                    accountStack.pop();
                }

                while (!accountQueue.empty())
                {
                    if (accountQueue.front().accountNumber != accountNumber)
                    {
                        tempQueue.push(accountQueue.front());
                    }
                    accountQueue.pop();
                }

                while (!tempStack.empty())
                {
                    accountStack.push(tempStack.top());
                    tempStack.pop();
                }

                while (!tempQueue.empty())
                {
                    accountQueue.push(tempQueue.front());
                    tempQueue.pop();
                }

                return;
            }

            prev = current;
            current = current->next;
        }

        cout << "Account not found. Please try again.\n";
    }

    void displayGraph()
    {
        accountGraph.displayGraph();
    }

    void displayStack()
    {
        stack<Account> tempStack = accountStack;
        cout << "Stack of Accounts:\n";
        while (!tempStack.empty())
        {
            Account currentAccount = tempStack.top();
            cout << "Account Number: " << currentAccount.accountNumber << endl;
            cout << "Account Name: " << currentAccount.accountName << endl;
            cout << "Balance: Rp. " << fixed << setprecision(2) << currentAccount.balance << endl;
            cout << endl;
            tempStack.pop();
        }
    }

    void displayQueue()
    {
        queue<Account> tempQueue = accountQueue;
        cout << "Queue of Accounts:\n";
        while (!tempQueue.empty())
        {
            Account currentAccount = tempQueue.front();
            cout << "Account Number: " << currentAccount.accountNumber << endl;
            cout << "Account Name: " << currentAccount.accountName << endl;
            cout << "Balance: Rp. " << fixed << setprecision(2) << currentAccount.balance << endl;
            cout << endl;
            tempQueue.pop();
        }
    }

    ~AccountList()
    {
        AccountNode *current = head;
        while (current != nullptr)
        {
            AccountNode *temp = current;
            current = current->next;
            delete temp;
        }
    }
};

int main()
{
    AccountList accounts;
    int choice;
    int accountNumber;
    string accountName;
    float balance;
    float amount;

    do
    {
        cout << "ATM Menu:\n";
        cout << "1. Create new account\n";
        cout << "2. Deposit\n";
        cout << "3. Delete account\n";
        cout << "4. Display all accounts\n";
        cout << "5. Display graph of accounts\n";
        cout << "6. Display stack of accounts\n";
        cout << "7. Display queue of accounts\n";
        cout << "8. Exit\n";
        cout << "Enter your choice (1-8): ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter account number: ";
            cin >> accountNumber;
            cout << "Enter account name: ";
            cin.ignore();
            getline(cin, accountName);
            cout << "Enter balance: Rp. ";
            cin >> balance;
            accounts.createAccount(accountNumber, accountName, balance);
            break;
        case 2:
            cout << "Enter account number: ";
            cin >> accountNumber;
            cout << "Enter deposit amount: Rp. ";
            cin >> amount;
            accounts.deposit(accountNumber, amount);
            break;
        case 3:
            cout << "Enter account number: ";
            cin >> accountNumber;
            accounts.deleteAccount(accountNumber);
            break;
        case 4:
            accounts.displayAccounts();
            break;
        case 5:
            cout << "Graph of Accounts:\n";
            accounts.displayGraph();
            break;
        case 6:
            accounts.displayStack();
            break;
        case 7:
            accounts.displayQueue();
            break;
        case 8:
            cout << "Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 8);

    return 0;
}