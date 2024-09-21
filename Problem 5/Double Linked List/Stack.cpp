#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <ctime>
#include <bitset>
using namespace std;

void LogFile(const string& event) {
    ofstream BinFile("Machine_Code_Stack.txt", ios_base::app);
    if (BinFile.is_open())
    {
        for (char c : event)
        {
            BinFile << bitset<8>(c) << " ";
        }
        BinFile << endl;
        BinFile.close();
    }
}

// Doubly linked list node structure
struct Node {
    int x;
    Node *next;
    Node *prev;
};
typedef Node ST;

void push(ST*&start, int& val)
{
    ST* newNode = new ST;
    newNode->x = val;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (start == NULL)
    {
        start = newNode;  // Stack is empty, so newNode becomes the start
    }
    else
    {
        start->prev = newNode;  // Link the new node to the current start
        newNode->next = start;  // Link newNode's next to the old start
        start = newNode;        // Update start to point to newNode
    }
    cout << "Item Pushed!" << endl;
    LogFile("Pushed value " + to_string(val));
}

int pop(ST*& start)
{
    if (start == NULL)
    {
        cout << "Underflow!" << endl;
        return 0;
    }
    else
    {
        ST* ptr = start;
        int value = ptr->x;
        start = start->next;  // Move start to the next node
        if (start != NULL)
            start->prev = NULL;  // Break the backward link for the new start
        delete ptr;  // Free the popped node
        cout << "Item Popped!" << endl;
        LogFile("Popped value " + to_string(value));
        return value;
    }
}

void traverse(ST*& start)
{
    ST* ptr = start;
    if (start == NULL)
    {
        cout << "Underflow!" << endl;
        return;
    }
    else {
        cout << "Traversed List: ";
        while (ptr != NULL)
        {
            cout << ptr->x << " ";
            ptr = ptr->next;
        }
        cout << endl;
    }
    LogFile("Traversed Stack List");
}

int peek(ST*& start)
{
    if (start == NULL)
    {
        cout << "Underflow!" << endl;
        return 0;
    }
    else
    {
        cout << "Peeked Value: " << start->x << endl;
        LogFile("Peeked value " + to_string(start->x));
        return start->x;
    }
}

int main()
{
    LogFile("Open File");
    ST *ptr = NULL;
    int z;
    while (true) {
        cout << "\n\nWelcome to Stack Manager:" << endl;
        cout << "Select Your Commands:" << endl;
        cout << "1. Push an element into a Stack" << endl;
        cout << "2. Pop an element from the Stack" << endl;
        cout << "3. Traverse a Stack" << endl;
        cout << "4. Peek Your Stack" << endl;
        cout << "5. Exit Program." << endl;
        cout << "Enter choice: "; cin >> z;
        switch (z)
        {
        case 1:
            LogFile("Call Push Function");
            {
                int value;
                cout << "Enter Value to Push: "; cin >> value;
                push(ptr, value);
            }
            break;
        case 2:
            LogFile("Call Pop Function");
            cout << pop(ptr) << endl;
            break;
        case 3:
            LogFile("Call Traverse Function");
            traverse(ptr);
            break;
        case 4:
            LogFile("Call Peek Function");
            peek(ptr);
            break;
        case 5:
            LogFile("Close File");
            while (ptr != NULL) {
                pop(ptr);  // Free all remaining nodes
            }
            return 0;
        default:
            LogFile("Force to close File");
            return 0;
        }
    }
}
