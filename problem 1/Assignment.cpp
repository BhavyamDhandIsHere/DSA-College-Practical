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
    print(a,n);    

}

void Add(int a[], int &n, int v)
{
    if (n == 0)
    {
        a[0] = v;
        n++;
    }
    else
    {
        int i;
        for (i = n - 1; (i >= 0 && a[i] > v); i--)
        {
            a[i + 1] = a[i];
        }
        a[i + 1] = v;
        n++;
    }
    print(a,n);    

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
    print(a,n);
}
void Delete(int a[], int n)
{
    int d;
    cout<<"enter the index which you want to delete:";
    cin>>d;
    if (d < 0 || d >= n) {
        cout << "Index out of bounds" << endl;
        return;
    }
    cout<<"Array produced is: [";
    for (int i = 0; i < n; i++)
    {
        if (i==d)
        {
            continue;
        }
        else
        {
            cout << a[i];
                if (i < n - 1)
            {
                cout << ", ";
            }
        }
        
    }
    cout<<"]"<<endl;
}

void max_or_min(int a[],int n)
{

    int max=a[0];
    for (int i = 1; i < n; i++)
    {
        if (max<a[i])
        {
            max=a[i];
        }
    }
        

    int min=a[0];
    for (int i = 0; i < n; i++)
    {
        if (min>a[i])
        {
            min=a[i];
        }
        
    }
    cout<<"the largest element of array is:"<<max<<endl;
    cout<<"the smallest element of array is:"<<min<<endl;

}

int main()
{
    
    int a[10]={10,20,30,40,50,60},x,v,n=6;
    print(a,n);
    cout<<"Choose what operation you want to execute for the Array:\n1:Add an element to Array\n2:Insert/Add an element at the desired location in the array\n3:Delete an ELement from the Array\n4:Update an Element associated with a pocket of an array\n5: Find Max and Min of Array"<<endl;
    cin>>x;
    switch (x)
    {
    case 1:
        cout<<"Enter whatever value you want to add in an array: ";
        cin>>v;
        Add(a,n,v);
        break;
    case 2:
        cout<<"Enter whatever value you want to add in an array: ";
        cin>>v;
        Insert(a,n,v);
        break;
    case 3:
        Delete(a,n);
        break;
    case 4:
        Update(a,n);
        break;
    case 5:
        max_or_min(a,n);
        break;
    default:
    cout<<"Insufficient Input. Try Again.";
        break;
    }
    return 0;
}