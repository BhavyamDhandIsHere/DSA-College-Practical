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

    // If the queue is empty, set front and rear
    if (F == NULL && R == NULL)
    {
        F = R = NewNode;
    }
    else if (data < F->num)  // Insert at the front
    {
        NewNode->next = F;
        F = NewNode;
    }
    else // Insert in the sorted position
    {
        Q* temp = F;
        Q* prev = NULL;

        // Traverse to find the correct position
        while (temp != NULL && temp->num <= data)
        {
            prev = temp;
            temp = temp->next;
        }

        // Insert in the middle or at the end
        prev->next = NewNode;
        NewNode->next = temp;

        // If inserted at the end, update the rear pointer
        if (temp == NULL)
        {
            R = NewNode;
        }
    }

    LogFile("Inserted element: " + to_string(data));
}


// Delete element from the queue
void deleteElement(Q*& F, Q*& R, int data)
{
    if (F == NULL)
    {
        cout << "Queue underflow" << endl;
        LogFile("Queue underflow - Delete failed");
        return;
    }

    Q* temp = F;
    Q* prev = NULL;

    // If the element to be deleted is the first element
    if (F->num == data)
    {
        F = F->next;
        // If it was the only element in the queue
        if (F == NULL)
        {
            R = NULL;  // The queue is now empty
        }
        cout << "Deleted element: " << temp->num << endl;
        LogFile("Deleted element: " + to_string(temp->num));
        delete temp;
        return;
    }

    // Traverse to find the element to delete
    while (temp != NULL && temp->num != data)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) // Element not found
    {
        cout << "Element not found in the queue" << endl;
        LogFile("Element not found in the queue - Delete failed");
        return;
    }

    // Unlink the node from the list
    prev->next = temp->next;

    // If the node to be deleted is the last node, update the rear pointer
    if (temp == R)
    {
        R = prev;
    }

    cout << "Deleted element: " << temp->num << endl;
    LogFile("Deleted element: " + to_string(temp->num));
    delete temp;
}

// Traverse the queue and print elements
void Traverse(Q* F)
{
    if (F == NULL)
    {
        cout << "Queue is empty" << endl;
        LogFile("Queue is empty - Traverse");
        return;
    }

    cout << "Queue elements: ";
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
                cout << "Enter element to delete: ";
                cin >> data;
                deleteElement(front, rear,data);
                break;
            case 3:
                Traverse(front);
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
