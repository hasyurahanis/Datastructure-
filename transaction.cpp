#include <iostream>
#include <cstring>
#include "transaction.h"

using namespace std;

void addTransaction(Transaction*& head, const char categories[][30], int categoryCount) {
    Transaction* newNode = new Transaction;

    cout << "Enter ID: ";
    cin >> newNode->id;
    cout << "Enter Date (YYYY-MM-DD): ";
    cin >> newNode->date;

    // Show categories from array
    cout << "Select Category:\n";
    for (int i = 0; i < categoryCount; i++) {
        cout << i + 1 << ". " << categories[i] << "\n";
    }
    int catChoice;
    do {
        cout << "Enter choice (1-" << categoryCount << "): ";
        cin >> catChoice;
    } while (catChoice < 1 || catChoice > categoryCount);

    strcpy_s(newNode->category, sizeof(newNode->category), categories[catChoice - 1]);


    cout << "Enter Amount: ";
    cin >> newNode->amount;

    cout << "Enter Description: ";
    cin.ignore();
    cin.getline(newNode->description, 100);

    newNode->next = nullptr;

    // Insert at end
    if (head == nullptr) {
        head = newNode;
    }
    else {
        Transaction* temp = head;
        while (temp->next != nullptr)
            temp = temp->next;
        temp->next = newNode;
    }

    cout << "Transaction added!\n";
}

void viewTransactions(Transaction* head) {
    if (head == nullptr) {
        cout << "No transactions yet.\n";
        return;
    }

    Transaction* temp = head;
    cout << "\n--- Transaction List ---\n";
    while (temp != nullptr) {
        cout << "ID: " << temp->id << "\n";
        cout << "Date: " << temp->date << "\n";
        cout << "Category: " << temp->category << "\n";
        cout << "Amount: RM" << temp->amount << "\n";
        cout << "Description: " << temp->description << "\n";
        cout << "-----------------------\n";
        temp = temp->next;
    }
}

void deleteTransaction(Transaction*& head, int id) {
    if (head == nullptr) {
        cout << "No transactions to delete.\n";
        return;
    }

    Transaction* temp = head;
    Transaction* prev = nullptr;

    while (temp != nullptr && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Transaction with ID " << id << " not found.\n";
        return;
    }

    if (prev == nullptr) {  // Deleting head
        head = head->next;
    }
    else {
        prev->next = temp->next;
    }

    delete temp;
    cout << "Transaction deleted.\n";
}

Transaction* searchTransaction(Transaction* head, int id) {
    Transaction* temp = head;
    while (temp != nullptr) {
        if (temp->id == id) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

// Bubble sort for linked list by amount (ascending)
void sortTransactionsByAmount(Transaction*& head) {
    if (head == nullptr || head->next == nullptr) return;

    bool swapped;
    do {
        swapped = false;
        Transaction* current = head;
        Transaction* prev = nullptr;
        Transaction* next = nullptr;

        while (current->next != nullptr) {
            next = current->next;
            if (current->amount > next->amount) {
                // Swap nodes
                if (prev == nullptr) {
                    // Swap head and next
                    current->next = next->next;
                    next->next = current;
                    head = next;
                    prev = next;
                }
                else {
                    prev->next = next;
                    current->next = next->next;
                    next->next = current;
                    prev = next;
                }
                swapped = true;
            }
            else {
                prev = current;
                current = current->next;
            }
        }
    } while (swapped);

    cout << "Transactions sorted by amount.\n";
}

void menu() {
    // Define categories array (Array data structure)
    const char categories[MAX_CATEGORIES][30] = {
        "Food",
        "Transport",
        "Entertainment",
        "Utilities",
        "Others"
    };

    Transaction* head = nullptr;
    int choice;

    do {
        cout << "\n--- Personal Finance Tracker ---\n";
        cout << "1. Add Transaction\n";
        cout << "2. View Transactions\n";
        cout << "3. Delete Transaction\n";
        cout << "4. Search Transaction by ID\n";
        cout << "5. Sort Transactions by Amount\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addTransaction(head, categories, MAX_CATEGORIES);
            break;
        case 2:
            viewTransactions(head);
            break;
        case 3: {
            int id;
            cout << "Enter Transaction ID to delete: ";
            cin >> id;
            deleteTransaction(head, id);
            break;
        }
        case 4: {
            int id;
            cout << "Enter Transaction ID to search: ";
            cin >> id;
            Transaction* found = searchTransaction(head, id);
            if (found != nullptr) {
                cout << "Transaction Found:\n";
                cout << "ID: " << found->id << "\n";
                cout << "Date: " << found->date << "\n";
                cout << "Category: " << found->category << "\n";
                cout << "Amount: RM" << found->amount << "\n";
                cout << "Description: " << found->description << "\n";
            }
            else {
                cout << "Transaction not found.\n";
            }
            break;
        }
        case 5:
            sortTransactionsByAmount(head);
            break;
        case 0:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    // Cleanup linked list before exit
    while (head != nullptr) {
        Transaction* temp = head;
        head = head->next;
        delete temp;
    }
}
