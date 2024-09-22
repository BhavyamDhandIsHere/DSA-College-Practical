#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <ctime>
#include <bitset>
using namespace std;

void LogFile(const string& event) {
    ofstream BinFile("Machine_Code_Queue.txt",ios_base::app);
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

const int maxsize=25;
void insertElement(int Q[],int info,int size,int &R, int &F)
{
    // Overflow check
    if (R==size-1)
    {
        cout<<"Overflow!"<<endl;
        return;
    }
    //Empty queue check
    if (F==-1||R==-1)
    {
        F=R=0;
        Q[R]=info;
    }
    else{
        ++R;
        Q[R]=info;
        for (int i = R; i > F; i--)
        {
            if (Q[i] < Q[i - 1])
            {
                swap(Q[i], Q[i - 1]);
            }
        }
    }
    
    LogFile("Inserted "+ to_string(info)+" In Queue ");
    return;
}
void deleteElement(int Q[], int &R, int &F, int data)
{
    // Empty queue check
    if (F == -1 || F > R)
    {
        cout << "Underflow!" << endl;
        return;
    }
    else
    {
        int i = F;
        bool found = false;
        // Search for the element
        for (; i <= R; i++)
        {
            if (Q[i] == data)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            cout << "Element not found!" << endl;
            return;
        }
        // Shift elements left to remove the found element
        for (int j = i; j < R; j++)
        {
            Q[j] = Q[j + 1];
        }
        R--; // Reduce the rear index
        if (R < F)
        {
            F = R = -1; // Queue becomes empty
        }
    }
    LogFile("Deleted Element from Queue");
}
void Traverse(int Q[], int size, int R, int F)
{
    if (F==-1||F>R)
    {
        cout<<"Underflow!"<<endl;
        return;
    }
    int x=F;
    cout<<"Elements of Queue will be: "<<endl;
    while (x <= R)
    {
        cout<<Q[x]<<endl;
        ++x;
    }
    LogFile("Traverse Queue");
}
int main()
{
    LogFile("Open File");
    int queue[maxsize],front=-1,rear=-1,z;
    while (true)
    {
        cout<<"\n\nWelcome to Queue Manager\n\n"<<endl;
        cout<<"Select Commands"<<endl;
        cout<<"1. Insert element"<<endl;
        cout<<"2. Delete element"<<endl;
        cout<<"3. Traverse Queue"<<endl;
        cout<<"4. Quit Program\n\n"<<endl;
        cout<<"Choose Your Command: "; cin>>z;
        switch (z)
        {
        case 1:
            LogFile("Call InsertElement Function");
            {
                int info;
                cout<<"Enter info you want to enter: ";cin>>info;
                insertElement(queue,info,maxsize,rear,front);
            }
            break;
        case 2:
            LogFile("Call InsertElement Function");
            {
                int info;
                cout<<"enter element to be deleted:"; cin>>info;
                deleteElement(queue,rear,front,info);
            } 
            break;
        case 3:
            LogFile("Call Traverse Function");
            Traverse(queue,maxsize,rear,front);
            break;
        case 4:
            return 0;
        default:
            break;
        }
    }
}