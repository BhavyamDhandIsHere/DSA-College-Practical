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
const int SIZE=10;
bool IsFull(int size,int& Tos)
{
    LogFile("Stack is Full");
    return(Tos==size-1);
}
bool IsEmpty(int& Tos)
{
    LogFile("Stack is Empty");
    return(Tos==-1);
}
void Push(int Stack[],int size,int& Tos,int info)
{
    // To check if Stack is full
    LogFile("Pushed Value " +to_string(info)+" to Stack");
    if (IsFull(size,Tos))
    {
        cout<<"\nStack Overflow!"<<endl;
        return;
    }
    else
        Stack[++Tos]=info;
}
int pop(int Stack[],int &Tos)
{
    LogFile("Popped Value from Stack");
    // To check if Stack is Empty
    if (IsEmpty(Tos))
    {
        cout<<"\nStack Underflow!"<<endl;
        return 0;
    }
    else
        return Stack[Tos--];
}
void traverse(int Stack[], int BStack[], int size, int& Tos, int& BTos) {
    if (IsEmpty(Tos)) {
        cout << "\nStack is empty!" << endl;
        return;
    }

    int info;
    int tempTos = Tos; // Save the original Tos for restoring later

    cout << "\nThe elements of Stack are:" << endl;

    // Move elements from Stack to BStack and print them
    while (!IsEmpty(Tos)) {
        info = pop(Stack, Tos);
        Push(BStack, size, BTos, info);
        cout << info << endl;
    }

    // Restore elements from BStack back to Stack
    while (!IsEmpty(BTos)) {
        info = pop(BStack, BTos);
        Push(Stack, size, Tos, info);
    }

    Tos = tempTos; // Restore original Tos
    LogFile("traversing List");
}

int Peek(int Stack[],int& Tos)
{
    LogFile("Peeked List");
    if (IsEmpty(Tos))
    {
        cout<<"\nStack Underflow!"<<endl;
        return 0;
    }
    return Stack[Tos];
}
int main()
{
    LogFile("Open File");
    int ToS=-1,BToS=-1;
    int S[SIZE],BS[SIZE];
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
                int info;
                cout<<"Enter info you want to push in Stack: "; cin>>info;
                Push(S,SIZE,ToS,info);
            }
            break;
        case 2:
            LogFile("Call Pop Function");
            pop(S,ToS);
            break;
        case 3:
            LogFile("Call Traverse Function");
            traverse(S,BS,SIZE,ToS,BToS);
            break;
        case 4:
            LogFile("Call Peek Function");
            cout<<Peek(S,ToS)<<endl<<endl;
            break;
        case 5:
            LogFile("Close File");
            return 0;
        default:
            LogFile("Force to close File");
            cout<<"Entered Invalid Option."<<endl;
            return 0;
            break;
        }
    }
}