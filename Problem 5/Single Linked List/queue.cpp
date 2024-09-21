#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <ctime>
#include <bitset>
using namespace std;

void LogFile(const string& event) {
    ofstream BinFile("Machine_Code_Queue.txt", ios_base::app);
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

struct Node
{
    int num;
    Node* next;
};

typedef Node Q;

// Insert element in the queue
void insertElement(Q*& F, Q*& R, int data)
{
    Q* NewNode = new Q;
    NewNode->num = data;
    NewNode->next = NULL;

    // Check if the queue is empty
    if (F == NULL && R == NULL)
    {
        F = R = NewNode;
    }
    else
    {
        R->next = NewNode;
        R = NewNode;
    }

    LogFile("Inserted element: " + to_string(data));
}

// Delete element from the queue
void deleteElement(Q*& F, Q*& R)
{
    if (F == NULL)
    {
        cout << "Queue underflow" << endl;
        LogFile("Queue underflow - Delete failed");
        return;
    }

    Q* temp = F;
    if (F == R) // Queue has only one node
    {
        F = R = NULL;
    }
    else
    {
        F = F->next;
    }

    cout << "Deleted element: " << temp->num << endl;
    LogFile("Deleted element: " + to_string(temp->num));
    delete temp;
}

// Traverse the queue and print elements
void Traverse(Q*& F, Q*& R)
{
    if (F == NULL)
    {
        cout << "Queue is empty" << endl;
        LogFile("Queue is empty - Traverse");
        return;
    }

    Q* temp = F;
    while (temp != NULL)
    {
        cout << temp->num << " ";
        temp = temp->next;
    }
    cout << endl;
    LogFile("Traversed queue");
}

int main()
{
    int z;
    int data;
    Q* front = NULL;
    Q* rear = NULL;
    
    LogFile("Opened File");

    while (true)
    {
        cout << "\n\nWelcome to Queue Manager\n\n" << endl;
        cout << "Select Commands" << endl;
        cout << "1. Insert element" << endl;
        cout << "2. Delete element" << endl;
        cout << "3. Traverse Queue" << endl;
        cout << "4. Quit Program\n\n" << endl;
        cout << "Choose Your Command: "; 
        cin >> z;

        switch (z)
        {
            case 1:
                cout << "Enter element to insert: ";
                cin >> data;
                insertElement(front, rear, data);
                break;
            case 2:
                deleteElement(front, rear);
                break;
            case 3:
                Traverse(front, rear);
                break;
            case 4:
                LogFile("Exiting Program");
                exit(0);
            default:
                cout << "Invalid command" << endl;
        }
    }
    return 0;
}
