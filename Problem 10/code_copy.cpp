#include <bits/stdc++.h>
#include <fstream>
using namespace std;

#define M 50
#define STRING_LEN 50
#define EMPTY -1
#define DELETED -2

struct Employee {
    int KeyID;
    char name[STRING_LEN];
    int age;
    char gender[1];
    long long int PhoneNo;
    char Email[STRING_LEN];
    char Qualifications[8];
    bool Occupied;
};


int HashFunction(int key) {
    if (key<1000||key>9999)
        return -1;
    else
    return key % M;
}

void InitializeHashTable(Employee HT[]) {
    for (int i = 0; i < M; i++) {
        HT[i].KeyID = EMPTY;
        strcpy(HT[i].name, "");
        HT[i].age=0;
        strcpy(HT[i].gender, "");
        HT[i].PhoneNo=0;
        strcpy(HT[i].Email, "");
        strcpy(HT[i].Qualifications, "");
        HT[i].Occupied = false;
    }
}

void InsertEmployee(Employee HT[], int key) {
    int index = HashFunction(key);
    int originalIndex = index;

    while (HT[index].Occupied && HT[index].KeyID != EMPTY) {
        index = HashFunction(index + 1);
        if (index == originalIndex) {
            cout << "Hash Table is Full!" << endl;
            return;
        }
    }
    HT[index].KeyID = key;
    cin.ignore();
    cout<<"enter name: ";
    cin.getline(HT[index].name, STRING_LEN);
    cout<<"enter age: ";
    cin>>HT[index].age;
    cout<<"enter gender: ";
    cin>>HT[index].gender;
    cout<<"enter Phone Number: ";
    cin>>HT[index].PhoneNo;
    cin.ignore();
    cout<<"enter Email-id: ";
    cin.getline(HT[index].Email, STRING_LEN);
    cout<<"enter Qualifications: ";
    cin.getline(HT[index].Qualifications,8);
    HT[index].Occupied = true;

}

void SearchEmployee(Employee HT[], int key) {
    int index = HashFunction(key);
    int originalIndex = index;

    while (HT[index].Occupied) {
        if (HT[index].KeyID == key) {
            cout << "Employee found at index " << index << ": " 
                 << HT[index].name<<",Age: "<<HT[index].age<<",Gender: "<<HT[index].gender<<", Phone Number: "<<HT[index].PhoneNo
                 <<",Email-id: "<<HT[index].Email<<",Qualifications: "<<HT[index].Qualifications << endl;
            return;
        }
        index = HashFunction(index + 1);
        if (index == originalIndex) {
            break;
        }
    }
    cout << "Employee not found." << endl;
}

void DeleteEmployee(Employee HT[], int key) {
    int index = HashFunction(key);
    int originalIndex = index;

    while (HT[index].Occupied) {
        if (HT[index].KeyID == key) {
            HT[index].KeyID = DELETED;
            strcpy(HT[index].name, "");
            HT[index].age=0;
            strcpy(HT[index].gender, "");
            HT[index].PhoneNo=0;
            strcpy(HT[index].Email, "");
            strcpy(HT[index].Qualifications, "");
            HT[index].Occupied = false;

            return;
        }
        index = HashFunction(index + 1);
        if (index == originalIndex) break;
    }
    cout << "Employee not found. Cannot delete element." << endl;
}

void UpdateEmployee(Employee HT[], int key)
{
    int index = HashFunction(key);
    int originalIndex = index;

    while (HT[index].Occupied)
    {
        if (HT[index].KeyID==key)
        {
            cout<<"Update information for KeyID: "<<key<<" and index: "<<index<<endl;
            cin.ignore();
            cout<<"enter name: ";
            cin.getline(HT[index].name, STRING_LEN);
            cout<<"enter age: ";
            cin>>HT[index].age;
            cout<<"enter gender: ";
            cin>>HT[index].gender;
            cout<<"enter Phone Number: ";
            cin>>HT[index].PhoneNo;
            cout<<"enter Email-id: ";
            cin.getline(HT[index].Email, STRING_LEN);
            cout<<"enter Qualifications: ";
            cin.getline(HT[index].Qualifications,8);
        }
        
    }
}

void DisplayTable(Employee HT[]) {
    cout << "\nHash Table:" << endl;
    for (int i = 0; i < M; i++) {
        if (HT[i].Occupied && HT[i].KeyID != EMPTY) {
            cout<< "Index: " << i << " Key: " << HT[i].KeyID<<", Name: "
                << HT[i].name<<",Age: "<<HT[i].age<<",Gender: "<<HT[i].gender<<", Phone Number: "<<HT[i].PhoneNo
                <<",Email-id: "<<HT[i].Email<<",Qualifications: "<<HT[i].Qualifications << endl;
        } else {
            cout << "Index: " << i << " Empty" << endl;
        }
    }
}

int main() {
    Employee HT[M];
    InitializeHashTable(HT);
    ifstream FP;
    FP.open("EMP.dat");
    FP.close();
    int choice, key;

    do {
        cout << "\n--- Hash Table Menu ---\n";
        cout << "1. Insert Employee\n";
        cout << "2. Search Employee\n";
        cout << "3. Delete Employee\n";
        cout << "4. Update Employee\n";
        cout << "5. Display Hash Table\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Key: ";
                cin >> key;
                if (HashFunction(key)==-1)
                {
                    cout<<"Key must be 4 digits!"<<endl;
                    break;
                }
                InsertEmployee(HT, key);
                break;
            case 2:
                cout << "Enter Key to search: ";
                cin >> key;
                SearchEmployee(HT, key);
                break;
            case 3:
                cout << "Enter Key to delete: ";
                cin >> key;
                DeleteEmployee(HT, key);
                break;
            case 4:
                cout << "Enter Key to delete: ";
                cin >> key;
                UpdateEmployee(HT,key);
            case 5:
                DisplayTable(HT);
                break;            
            case 6:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
