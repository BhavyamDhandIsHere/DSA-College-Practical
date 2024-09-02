#include <iostream>
using namespace std;

void print(int a[], int n)
{
    cout<<"Array produced is: [";
    for (int i = 0; i < n; i++)
    {
        cout<<a[i];
        if (i < n - 1)
        {
            cout << ", ";
        }
    }
    cout<<"]"<<endl;

}

void Insert(int a[], int &n, int v)
{
    int d;
    cout << "Enter the index where you want to insert an element: ";
    cin >> d;

    if (d < 0 || d > n) {
        cout << "Invalid index!" << endl;
        return;
    }

    for (int j = n; j > d; j--)
    {
        a[j] = a[j - 1];
    }
    a[d] = v;
    n++;
}

int main()
{
    
    int a[10]={4,9,5,3,1,4},x,d;
    int n=6;
    print(a,n);
    Insert(a,n,32);
    print(a,n);
}