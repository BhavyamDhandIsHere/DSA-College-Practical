#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <ctime>
#include <bitset>
using namespace std;

// Function to write in Log file
void LogFile(const string& event) {
    ofstream BinFile("Machine_Code_Stack.txt", ios_base::app);
    if (BinFile.is_open()) {
        for (char c : event) {
            BinFile << bitset<8>(c) << " ";
        }
        BinFile << endl;
        BinFile.close();
    }
}

struct BTree{
    int Data;
    BTree* LST;
    BTree* RST;
};

void EnterNode(BTree*x, int d)
{
    x->Data = d;
    x->LST = NULL;
    x->RST = NULL;
}

BTree* CreateTree(BTree* head)
{
    int d;
    cout << "Enter Node Data: "; cin >> d;
    if (d == -1) // If user enters -1, it signifies no node should be added.
    {
        return NULL;
    }
    head = new BTree; // Allocate memory for a new node
    EnterNode(head, d);

    cout << "Enter the Left Node of current Node " << d << ": "; 
    head->LST = CreateTree(head->LST);
    if (head->LST==NULL)
        return head;
    cout << "Enter the Right Node of current Node " << d << ": "; 
    head->RST = CreateTree(head->RST);
    return head;
}

// To print Binary Tree height
int TreeHeight(BTree* head)
{
    if (head==NULL)
        return 0;
    else {
        int LHeight = TreeHeight(head->LST);
        int RHeight = TreeHeight(head->RST);
        if (LHeight > RHeight)
            return (LHeight + 1);
        else
            return (RHeight + 1);
    }
}

void PrintCurrentLevel(BTree* head, int level)
{
    if (head == NULL)
        return;
    if (level == 1)
        cout << head->Data << " ";
    else if (level > 1)
    {
        PrintCurrentLevel(head->LST, level - 1);
        PrintCurrentLevel(head->RST, level - 1);
    }
}

void PrintLevelOrder(BTree* head)
{
    int h = TreeHeight(head), i;
    for (i = 1; i <= h; i++) // Start at level 1
        PrintCurrentLevel(head, i);
}

// For Preorder Traversal (head->left->right)
void PreOrder(BTree* head)
{
    if (head==NULL)
        return;
    cout << head->Data << " ";
    PreOrder(head->LST);
    PreOrder(head->RST);
}

// For Inorder Traversal (left->head->right)
void InOrder(BTree* head)
{
    if (head==NULL)
        return;
    InOrder(head->LST);
    cout << head->Data << " ";
    InOrder(head->RST);
}

// For Postorder Traversal (left->right->head)
void PostOrder(BTree* head)
{
    if (head==NULL)
        return;
    PostOrder(head->LST);
    PostOrder(head->RST);
    cout << head->Data << " ";
}

void DeleteTree(BTree* head)
{
    if (head == NULL)
        return;
    
    // First delete both subtrees
    DeleteTree(head->LST);
    DeleteTree(head->RST);
    
    // Then delete the node itself
    delete head;
}

int main()
{
    LogFile("Starting Program");
    int z;
    BTree* Head = NULL;
    cout << "Welcome to the Binary Tree Manager!" << endl;
    cout << "Create Binary Tree to continue:\nHead Node:" << endl;
    Head = CreateTree(Head);
    LogFile("Created a Binary Tree");
    
    // Userbase
    while (true)
    {
        cout << "\nEnter your Commands!" << endl;
        cout << "1. Print Tree" << endl;
        cout << "2. Preorder Traversal" << endl;
        cout << "3. Inorder Traversal" << endl;
        cout << "4. Postorder Traversal" << endl;
        cout<<"Click Any Else Button to close Program!"<<endl;
        cin >> z;
        
        switch (z)
        {
        case 1:
            cout << "Printing Tree: ";
            PrintLevelOrder(Head);
            LogFile("Printing Binary Tree as is");
            break;
        case 2:
            cout << "Preorder Traversal is: ";
            PreOrder(Head);
            cout << endl;
            LogFile("Printing Binary Tree Node in Preorder traversal form");
            break;
        case 3:
            cout << "Inorder Traversal is: ";
            InOrder(Head);
            cout << endl;
            LogFile("Printing Binary Tree Node in Inorder traversal form");
            break;
        case 4:
            cout << "Postorder Traversal is: ";
            PostOrder(Head);
            cout << endl;
            LogFile("Printing Binary Tree Node in Postorder traversal form");
            break;
        default:
            LogFile("Closing Program");
            DeleteTree(Head);
            return 0;
        }
    }    
}
