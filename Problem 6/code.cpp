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

int *CreateArray(ifstream &A,int n)
{
    int x, i=0,*arr=new int[n];
    while(A>>x&&i<n)
    {
        *(arr+i)=x;
        i++;
    }
    return arr;
}

int LinSearch(int *arr,int n,int x)
{
    for (int i = 0; i < n; i++)
    {
        if (*(arr+i)==x)
            return i;
    }
    return -1;
}
int BinSearch(int *arr,int n, int x)
{
    if (n==0)
    {
        cout<<"Array Underflow!"<<endl;
        return -1;
    }
    else{
        int low=0,high=n-1;
        int mid;
        while (*(arr+mid)!=x)
        {
            mid=(low+high)/2;
            if (*(arr+mid)<x)
                low=mid+1;
            else if (*(arr+mid)>x)
                high=mid-1;
            else if(*(arr+mid)==x)
                return mid;
        }
        cout<<"Element not found!"<<endl;
        return -1;
    }
}
void InsertionSort(int *arr,int n)
{
    for (int i = 1; i < n; i++)
    {
        int x=*(arr+i);
        int j = i-1;
        for (j; j >=0; j--)
            *(arr+j+1)=*(arr+j);
        *(arr+j+1)=x;
    }
}
void SelectionSort(int *arr,int n)
{
    int i,j;
    bool swapped;
    for (i = 0; i < n-1; i++)
    {
        int min=i;
        for (j = i+1; j < n; j++)
        {
            if (*(arr+j)<*(arr+min))
                min=j;
        }
        if (min!=i)
        {
            swap(*(arr+i),*(arr+min));
        }
    }
}


void BubbleSort(int *arr, int n)
{
    int i,j;
    bool swapped;
    for (i = 0; i < n; i++)
    {
        swapped=false;
        for (j = 0; j<n-1-i; j++)
        {
            if (*(arr+j)>*(arr+j+1))
                swap(*(arr+j),*(arr+j+1));
            swapped=true;
        }
        if (!swapped)
            break;
    }
}


int main()
{
    int n,choice,x;
    cout << "Enter the size of Array: ";
    cin >> n;

    ifstream infile("array.txt");
    if (!infile.is_open()) {
        cout << "Error: Unable to open the file!" << endl;
        return -1;
    }

    int *array = CreateArray(infile, n);
    infile.close();  // Close the file after reading the data

    cout << "Original Array:" << endl;
    for (int i = 0; i < n; i++) {
        cout << *(array + i) << " ";
    }
    cout << endl;
    cout<<"Select the Operation you want to execute on the Array:"; cin>>choice;
    switch (choice)
    {
    case 1:
        cout<<"Select element you want to Search Linearly: "; cin>>x;
        cout<<LinSearch(array,n,x);
        break;
    case 2:
        cout<<"Select element you want to Search Binarily: "; cin>>x;
        BinSearch(array,n,x);
    case 3:
        InsertionSort()
    default:
        break;
    }
    BubbleSort(array, n);

    cout << "Sorted Array:" << endl;
    for (int i = 0; i < n; i++) {
        cout << *(array + i) << " ";
    }
    cout << endl;
    ofstream OutFile("NewArray.txt");
    for (int i = 0; i < n; i++) {
        OutFile << *(array + i) << " ";
    }
    OutFile<<endl;
    delete[] array;
    return 0;
}