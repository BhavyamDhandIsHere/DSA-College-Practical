#include <iostream>
#include <string>
#include <fstream>
#include <cctype> // For isdigit function
using namespace std;

struct dateOfBirth {
    int day, year, month;
};

struct Society_Record {
    string Aadhar; // Aadhar is a string of digits
    string name;
    char gender[3];
    string Father_Name;
    string Mother_Name;
    dateOfBirth DOB;

    Society_Record* prev;
    Society_Record* next;
};

typedef Society_Record SR;

SR* pointToNode(SR* start, string Aadhar) {
    SR* ptr = start;
    while (ptr != nullptr) {
        if (ptr->Aadhar==Aadhar)
            return ptr;
        ptr = ptr->next;
    }
    return nullptr;
}

bool DATEValidity(int day, int month, int year) {
    if (year > 2024 || day < 1 || day > 31 || month < 1 || month > 12) {
        return false;
    }
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        return false;
    }
    if (month == 2) {
        bool leapyear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > (leapyear ? 29 : 28)) {
            return false;
        }
    }
    return true;
}

bool VerifyAadhar(SR*& start, const string& Aadhar) {
    if (Aadhar.length() != 12) {
        cout << "Aadhar must be exactly 12 digits long.\n";
        return false;
    }
    for (char c : Aadhar) {
        if (!isdigit(c)) {
            cout << "Aadhar must contain only digits.\n";
            return false;
        }
    }
    SR* ptr = start;
    while (ptr != nullptr) {
        if (ptr->Aadhar == Aadhar) {
            cout << "Aadhar already exists. Insertion failed.\n";
            return false;
        }
        ptr = ptr->next;
    }
    return true;
}

bool STRValidity(const string& str) {
    for (char c : str) {
        if (!isalpha(c) && c != '.' && c != ' ') return false;
    }
    return true;
}

void InputDetails(SR* ptr) {
    cin.ignore();
    do {
        cout << "\nName: "; getline(cin, ptr->name);
    } while (!STRValidity(ptr->name));
    do {
        cout << "\nGender (M/F): ";
        cin.getline(ptr->gender, 3); // Allow space for the null terminator
    } while (ptr->gender[0] != 'M' && ptr->gender[0] != 'F' && ptr->gender[0] != 'm' && ptr->gender[0] != 'f');

    do {
        cout << "\nFather Name: "; getline(cin, ptr->Father_Name);
    } while (!STRValidity(ptr->Father_Name));

    do {
        cout << "\nMother Name: "; getline(cin, ptr->Mother_Name);
    } while (!STRValidity(ptr->Mother_Name));

    while (true) {
        cout << "\nDate of Birth:\n\tDAY: "; cin >> ptr->DOB.day;
        cout << "\n\tMonth (1-12): "; cin >> ptr->DOB.month;
        cout << "\n\tYear: "; cin >> ptr->DOB.year;
        if (DATEValidity(ptr->DOB.day, ptr->DOB.month, ptr->DOB.year))
            break;
        else cout << "Invalid date. Please enter again.\n";
    }
}

void InsertRecord(SR*& start) {
    string Aadhar;
    cout << "\nAadhar Number (12 digits): "; getline(cin, Aadhar);
    if (!VerifyAadhar(start, Aadhar))
        return;

    SR* NewResident = new SR;
    NewResident->Aadhar = Aadhar;
    NewResident->next = nullptr;
    NewResident->prev = nullptr;

    InputDetails(NewResident);

    if (start == NULL) {
        start = NewResident;
    }
    else {
        SR* ptr = start;
        while (ptr->next != NULL) {
            ptr = ptr->next;
        }
        ptr->next = NewResident;
        NewResident->prev = ptr;
    }
    cout << "Resident Record Added." << endl;
}

void DeleteRecord(SR*& start, const string& Aadhar) {
    if (start == NULL) {
        cout << "List is Empty. UnderFlow observed." << endl;
        return;
    }
    SR* ptr = start;
    while (ptr != NULL) {
        if (ptr->Aadhar == Aadhar) {
            //check if it's not first
            if (ptr->prev != NULL) {
                ptr->prev->next = ptr->next;
            }
            else
                start = ptr->next;
            if (ptr->next != NULL) {
                ptr->next->prev = ptr->prev;
            }

            delete ptr;
            cout << "Resident Record Deleted." << endl;
            return;
        }
        ptr = ptr->next;
    }
}

void updateRecord(SR*& start, const string& Aadhar) {
    SR* ptr = pointToNode(start, Aadhar);

    if (ptr == nullptr) {
        cout << "Record Not Found!" << endl;
        return;
    }

    cout << "Updating Record for Aadhar: " << Aadhar << endl;
    InputDetails(ptr);

    cout << "Resident Record updated." << endl;
}

void SortRecords(SR*& start)
{
    if (start==nullptr)
        return;
    
    bool swapped;
    do
    {
        swapped=false;
        SR* ptr= start;
        while (ptr->next!=nullptr)
        {
            if (ptr->name >ptr->next->name)
            {
                swap(ptr->name,ptr->next->name);
                swap(ptr->Aadhar ,ptr->next->Aadhar);
                swap(ptr->Father_Name,ptr->next->Father_Name);
                swap(ptr->Mother_Name,ptr->next->Mother_Name);
                swap(ptr->gender,ptr->next->gender);
                swap(ptr->DOB,ptr->next->DOB);
                swapped=true;
            }
            ptr=ptr->next;
        }
    } while (swapped);
    cout<<"Records Sorted Successfully."<<endl;
}

void FindRecord(SR*&ptr)
{
    if (ptr==nullptr)
    {
        cout<<"Record Not Found!"<<endl;
        return;
    }
    cout<<"------------------------------------------------";
    cout<<"Resident Name: "<<ptr->name<<endl;
    cout<<"Aadhar No.: "<<ptr->Aadhar<<endl;
    cout<<"Father's name: "<<ptr->Father_Name<<endl;
    cout<<"Mother's name: "<<ptr->Mother_Name<<endl;
    cout<<"gender: "<<ptr->gender<<endl;
    cout<<"Date Of Birth: "<<ptr->DOB.day<<"-"<<ptr->DOB.month<<"-"<<ptr->DOB.year<<endl;
    cout<<"------------------------------------------------";

}
int main() {
    int z;
    SR* ptr = NULL;
    while (true) {
        cout << "ABC SOCIETY RESIDENT RECORD DATABASE MANAGER" << endl;
        cout << "Choose a Command:\n1. Insert a Record \n2. Delete a Record  \n3. Update a Record \n4. Keep the Records in sorted order\n5. Find a Record\n6. QUIT PROGRAM\n";
        cin >> z;
        switch (z) {
        case 1:
            InsertRecord(ptr);
            break;
        case 2:
            {
                string Aadhar;
                cin.ignore();
                cout << "Enter the Aadhar No. of the Required resident record.";
                getline(cin, Aadhar);
                DeleteRecord(ptr, Aadhar);
            }
            break;
        case 6:
            return 0;
        default:
            cout << "Invalid Option. Please choose again." << endl;
            break;
        }
    }
}