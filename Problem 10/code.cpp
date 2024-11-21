#include <bits/stdc++.h>
#include <fstream>
using namespace std;

#define M 50
#define STRING_LEN 50
#define EMPTY -1
#define DELETED -2

struct Employee {
    char name[STRING_LEN];
    char age[2];
    char gender[1];
    char PhoneNo[15];
    char Email[STRING_LEN];
    char Qualifications[8];
    bool Occupied;
};

struct HashTable
{
    vector<int> Key;
    vector<Employee> Table;

    int HashFunction(int key)
    {
        if(key<1000||key>9999)
            return -1;
        else return key%M;
    }
    void StartHashtable()
    {
        for (int i = 0; i < M; i++)
        {
            Key[i]=EMPTY;
            strcpy(Table[i].name,"");
            strcpy(Table[i].age,"");
            strcpy(Table[i].gender,"");
            strcpy(Table[i].PhoneNo,"");
            strcpy(Table[i].Email,"");
            strcpy(Table[i].Qualifications,"");
        }
        
    }
    int Insert(int key)
    {
        int index=HashFunction(key),OGIndex=index;

    }
};

int main()
{

}