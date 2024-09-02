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

void max_or_min(int a[],int n)
{
    cout<<"Find the Largest or smallest element of element: Choose 1 for Max and 2 for Min "<<endl;
    int ans;
    cin>>ans;
    if (ans==1)
    {
    int max=a[0];
    for (int i = 1; i < n; i++)
    {
        if (max<a[i])
        {
            max=a[i];
        }
        
    }
    cout<<"the largest element of array is:"<<max<<endl;
    }
    else if (ans==2)
    {
        int min=a[0];
        for (int i = 0; i < n; i++)
        {
            if (min>a[i])
            {
                min=a[i];
            }
            
        }
    cout<<"the smallest element of array is:"<<min<<endl;
    }
    else{
        cout<<"Error: Insufficent Input."<<endl;
    }
}

int main()
{
    
    int a[10]={4,9,5,3,1,4},x,d;
    int n=6;
    print(a,n);
    max_or_min(a,n);
    return 0;
}