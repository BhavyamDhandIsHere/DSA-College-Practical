#include <iostream>
using namespace std;

void bubbleSort(int a[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
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
}

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
int main()
{
    
    int a[10]={4,9,5,3,1,4};
    int n=6;
    bubbleSort(a,n);
    print(a,n);
    Add(a,n,7);
    print(a,n);
}