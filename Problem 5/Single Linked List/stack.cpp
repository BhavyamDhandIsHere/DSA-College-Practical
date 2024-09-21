#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <ctime>
#include <bitset>
using namespace std;

void LogFile(const string& event) {
    ofstream BinFile("Machine_Code_Stack.txt",ios_base::app);
    if (BinFile.is_open())
    {
        for (char c:event)
        {
            BinFile<<bitset<8>(c)<<" ";
        }
        BinFile<<endl;
        BinFile.close();
    }
    
}
struct Node{
    int x;
    Node *next;

};
typedef Node ST;
void push(ST*&start, int& val)
{
    ST*newNode=new ST;
    newNode->x=val;
    newNode->next=NULL;
    //check if list is empty
    if (start==NULL)
        start=newNode;
    else
    {
        newNode->next=start;
        start=newNode;
    }
    cout<<"Item Pushed!"<<endl;
    LogFile("Pushed value " + to_string(val));
}
int pop(ST*& start)
{
    // check if list is empty
    if (start==NULL)
    {
        cout<<"Underflow!"<<endl;
        return 0;
    }
    else
    {
        ST* ptr = start;
        int value = ptr->x;
        start = start->next;
        delete ptr;  // Free the popped node
        cout << "Item Popped!" << endl;
        LogFile("Popped value " + to_string(value));
        return value;
    }
    LogFile("Popped value ");
}
void traverse(ST*& Start)
{
    ST*ptr=Start;
    if (Start==NULL)
    {
        cout<<"Underflow!"<<endl;
        return;
    }
    else{
        cout<<"Traversed List will be:"<<endl;
        while (ptr!=NULL)
        {
            cout<<ptr->x<<" ";
            ptr=ptr->next;
        }
        return;
    }
    LogFile("Traversed Stack List");
}
int peek(ST*&start)
{
    if (start==NULL)
    {
        cout<<"Underflow!"<<endl;
        return 0;
    }
    else
    {
        return start->x;
    }
    LogFile("Peeked first Node");
}


int main()
{
    LogFile("Open File");
    ST *ptr=NULL;
    int z;
    while (true){
        cout<<"\n\nWelcome to Stack Manager:"<<endl;
        cout<<"Select Your Commands:"<<endl;
        cout<<"1. Push an element into a Stack"<<endl;
        cout<<"2. Pop an element from the Stack"<<endl;
        cout<<"3. Traverse a Stack"<<endl;
        cout<<"4. Peek Your Stack"<<endl;
        cout<<"5. Exit Program."<<endl;
        cout<<"Enter choice:"; cin>>z;
        switch (z)
        {
        case 1:
            LogFile("Call Push Function");
            {
                int value;
                cout<<"Enter Value to Push: "; cin>>value;
                push(ptr,value);
            }
            break;
        case 2:
            LogFile("Call Pop Function");
            cout<<pop(ptr)<<endl;
            break;
        case 3:
            LogFile("Call Traverse Function");
            traverse(ptr);
            break;
        case 4:
            LogFile("Call Peek Function");
            cout<<peek(ptr)<<endl;
            break;
        case 5:
            LogFile("Close File");
            while (ptr != NULL) {
                pop(ptr);  // Free all remaining nodes
            }
            return 0;
            break;
        default:
            LogFile("Force to close File");
            return 0;
            break;
        }
    }    
}