#include <iostream>
#include <string>
using namespace std;

// Inner Node for Expense
class ExpenseNode {
public:
    string name;
    float amount;
    ExpenseNode* next;

    ExpenseNode(string n, float a) {
        name = n;
        amount = a;
        next = NULL;
    }
};

// Outer Node for Month
class MonthNode {
public:
    string monthName;
    ExpenseNode* expenseHead;
    MonthNode* next;

    MonthNode(string m) {
        monthName = m;
        expenseHead = NULL;
        next = NULL;
    }
};

// Head of the outer list
MonthNode* monthHead = NULL;

// Function to add a new month
void addMonth(string m) {
    MonthNode* newMonth = new MonthNode(m);
    if (!monthHead) {
        monthHead = newMonth;
    } else {
        MonthNode* temp = monthHead;
        while (temp->next)
            temp = temp->next;
        temp->next = newMonth;
    }
    cout << "Month added.\n";
}

// Find a month node
MonthNode* findMonth(string m) {
    MonthNode* temp = monthHead;
    while (temp) {
        if (temp->monthName == m)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

// Add expense to a specific month
void addExpense(string month, string name, float amount) {
    MonthNode* mNode = findMonth(month);
    if (!mNode) {
        cout << "Month not found.\n";
        return;
    }
    ExpenseNode* newExp = new ExpenseNode(name, amount);
    if (!mNode->expenseHead) {
        mNode->expenseHead = newExp;
    } else {
        ExpenseNode* temp = mNode->expenseHead;
        while (temp->next)
            temp = temp->next;
        temp->next = newExp;
    }
    cout << "Expense added.\n";
}

// Display all months and expenses
void displayAll() {
    MonthNode* mTemp = monthHead;
    while (mTemp) {
        cout << "Month: " << mTemp->monthName << endl;
        ExpenseNode* eTemp = mTemp->expenseHead;
        while (eTemp) {
            cout << "  - " << eTemp->name << ": " << eTemp->amount << endl;
            eTemp = eTemp->next;
        }
        mTemp = mTemp->next;
    }
}

// Update an expense
void updateExpense(string month, string oldName, string newName, float newAmt) {
    MonthNode* mNode = findMonth(month);
    if (!mNode) return;
    ExpenseNode* temp = mNode->expenseHead;
    while (temp) {
        if (temp->name == oldName) {
            temp->name = newName;
            temp->amount = newAmt;
            cout << "Expense updated.\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Expense not found.\n";
}

// Delete an expense
void deleteExpense(string month, string name) {
    MonthNode* mNode = findMonth(month);
    if (!mNode) return;
    ExpenseNode* curr = mNode->expenseHead;
    ExpenseNode* prev = NULL;
    while (curr) {
        if (curr->name == name) {
            if (!prev)
                mNode->expenseHead = curr->next;
            else
                prev->next = curr->next;
            delete curr;
            cout << "Expense deleted.\n";
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    cout << "Expense not found.\n";
}

// Show most expensive item in a month
void mostExpensive(string month) {
    MonthNode* mNode = findMonth(month);
    if (!mNode || !mNode->expenseHead) {
        cout << "No expenses found.\n";
        return;
    }
    ExpenseNode* temp = mNode->expenseHead;
    ExpenseNode* maxExp = temp;
    while (temp) {
        if (temp->amount > maxExp->amount)
            maxExp = temp;
        temp = temp->next;
    }
    cout << "Most expensive in " << month << ": " << maxExp->name << " - " << maxExp->amount << endl;
}

// Menu
void menu() {
    int choice;
    string month, name, newName;
    float amount;

    while (true) {
        cout << "\nExpense Tracking System \n1. Add Month\n2. Add Expense\n3. Display All\n4. Update Expense\n5. Delete Expense\n6. Most Expensive\n7. Exit\nEnter: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter month name: ";
                getline(cin, month);
                addMonth(month);
                break;
            case 2:
                cout << "Enter month: ";
                getline(cin, month);
                cout << "Expense name: ";
                getline(cin, name);
                cout << "Amount: ";
                cin >> amount;
                addExpense(month, name, amount);
                break;
            case 3:
                displayAll();
                break;
            case 4:
                cout << "Month: ";
                getline(cin, month);
                cout << "Old name: ";
                getline(cin, name);
                cout << "New name: ";
                getline(cin, newName);
                cout << "New amount: ";
                cin >> amount;
                updateExpense(month, name, newName, amount);
                break;
            case 5:
                cout << "Month: ";
                getline(cin, month);
                cout << "Expense to delete: ";
                getline(cin, name);
                deleteExpense(month, name);
                break;
            case 6:
                cout << "Month: ";
                getline(cin, month);
                mostExpensive(month);
                break;
            case 7:
                return;
        }
    }
}

int main() {
    menu();
    return 0;
}
