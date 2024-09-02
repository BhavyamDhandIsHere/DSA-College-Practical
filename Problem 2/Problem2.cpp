#include <iostream>
#include <cstring>
using namespace std;

int const MAX=5;
struct Address{
    string House_No;
    string street;
    string city;
    string state;
    string country;
};
struct DOB
{
    string day;
    string month;
    string year;

};
struct StudentData
{
    string roll_no;
    string student;
    string father;
    string mother;
    string year_of_admission;
    DOB date_of_birth;
    string Class;
    string semester;
    string branch;
    Address add;
};

int main()
{
    StudentData Batch1[MAX];
    int n=0,x;
    while (true)
    {
        cout << "\n\nWelcome to the record manager program!\nEnter your desired choice:\n";
        cout << "1. Input an Entry\n2. Delete Entry from Record\n3. Search Entry from Record\n4. Display all Records\n5. Quit Program\n";
        cin >> x;
        cout<<"";

    }
    return 0;
}