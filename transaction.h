#ifndef TRANSACTION_H
#define TRANSACTION_H

struct Transaction {
    int id;
    char date[11];
    char category[30];
    float amount;
    char description[100];
    Transaction* next;
};

const int MAX_CATEGORIES = 5;

// Function declarations
void addTransaction(Transaction*& head, const char categories[][30], int categoryCount);
void viewTransactions(Transaction* head);
void deleteTransaction(Transaction*& head, int id);
Transaction* searchTransaction(Transaction* head, int id);
void sortTransactionsByAmount(Transaction*& head);
void menu();

#endif
