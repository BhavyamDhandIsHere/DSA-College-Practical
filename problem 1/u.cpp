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

void Update(int a[], int n)
{
    int x,v;
    cout<<"enter the pocket which you want to update: "<<endl;
    cin>>x;
    if (x < 0 || x >= n) {
        cout << "Index out of bounds" << endl;
        return;
    }
    cout<<"Enter value: ";
    cin>>v;
    a[x]=v;
    
}

int main()
{
    
    int a[10]={4,9,5,3,1,4},x,d;
    int n=6;
    print(a,n);
    Update(a,n);
    print(a,n);
}