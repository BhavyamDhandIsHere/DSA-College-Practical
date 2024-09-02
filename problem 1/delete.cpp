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
 
int main()
{
    int a[10]={4,9,5,3,1,4},x,d;
    int n=6;
    print(a,n);
    Delete(a,n);
}