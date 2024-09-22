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

// Doubly Linked List Node Structure
struct Node
{
    int num;
    Node* next;
    Node* prev;
};

typedef Node Q;

// Insert element in a sorted position
void insertElement(Q*& F, Q*& R, int data)
{
    Q* NewNode = new Q;
    NewNode->num = data;
    NewNode->next = NULL;
    NewNode->prev = NULL;

    // Case 1: If the list is empty
    if (F == NULL && R == NULL)
    {
        F = R = NewNode;
    }
    else
    {
        Q* temp = F;

        // Case 2: Insertion at the front (smallest element)
        if (data < F->num)
        {
            NewNode->next = F;
            F->prev = NewNode;
            F = NewNode;
        }
        else
        {
            // Traverse the list to find the correct position
            while (temp != NULL && temp->num <= data)
            {
                temp = temp->next;
            }

            // Case 3: Insertion at the end (largest element)
            if (temp == NULL)
            {
                NewNode->prev = R;
                R->next = NewNode;
                R = NewNode;
            }
            else
            {
                // Case 4: Insertion in the middle
                NewNode->next = temp;
                NewNode->prev = temp->prev;
                temp->prev->next = NewNode;
                temp->prev = NewNode;
            }
        }
    }

    LogFile("Inserted element in sorted order: " + to_string(data));
}

// Delete element with a specific value
void deleteByValue(Q*& F, Q*& R, int data)
{
    if (F == NULL)
    {
        cout << "Queue is empty, cannot delete." << endl;
        LogFile("Queue underflow - Delete by value failed");
        return;
    }

    Q* temp = F;

    // Traverse the list to find the node with the given value
    while (temp != NULL && temp->num != data)
    {
        temp = temp->next;
    }

    // Case 1: Element not found
    if (temp == NULL)
    {
        cout << "Element " << data << " not found in the queue." << endl;
        LogFile("Element not found in the queue - Delete failed");
        return;
    }

    // Case 2: Deleting the first node
    if (temp == F)
    {
        F = F->next;
        if (F != NULL)
        {
            F->prev = NULL;
        }
        else
        {
            R = NULL; // The list becomes empty
        }
    }
    // Case 3: Deleting the last node
    else if (temp == R)
    {
        R = R->prev;
        R->next = NULL;
    }
    // Case 4: Deleting from the middle
    else
    {
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
    }

    cout << "Deleted element: " << temp->num << endl;
    LogFile("Deleted element: " + to_string(temp->num));
    delete temp;
}

// Traverse the queue from front to rear
void Traverse(Q*& F)
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

// Traverse the queue in reverse from rear to front
void TraverseReverse(Q*& R)
{
    if (R == NULL)
    {
        cout << "Queue is empty" << endl;
        LogFile("Queue is empty - Reverse Traverse");
        return;
    }

    Q* temp = R;
    while (temp != NULL)
    {
        cout << temp->num << " ";
        temp = temp->prev;
    }
    cout << endl;
    LogFile("Traversed queue in reverse");
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
        cout << "1. Insert element (sorted)" << endl;
        cout << "2. Delete element by value" << endl;
        cout << "3. Traverse and Reverse Traverse Queue" << endl;
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
                deleteByValue(front, rear, data);
                break;
            case 3:
                cout << "Queue from front to rear: ";
                Traverse(front);
                cout << "Queue from rear to front: ";
                TraverseReverse(rear);
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
