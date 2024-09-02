#include <iostream>
#include <string>
#include <fstream>
#include <cctype> // For isdigit function
using namespace std;

void LogFile(const string &txt)
{
    ofstream log_file("logfile.txt",ios_base::out|ios_base::app);
    log_file<<txt<<endl;
}



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

bool DATEValidity(int day, int month, int year) {
    LogFile("Check if Date Prompts by User are Correct or Not");
    if (year > 2024 || day < 1 || day > 31 || month < 1 || month > 12) {
        LogFile("Invalid Date added, retry.");
        return false;
    }
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        LogFile("Invalid Date added, retry.");
        return false;
    }
    if (month == 2) {
        bool leapyear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > (leapyear ? 29 : 28)) {
            LogFile("Invalid Date added, retry.");
            return false;
        }
    }
    LogFile("Date Prompt is added.");
    return true;
}

bool VerifyAadhar(SR*& start, const string& Aadhar) {
    LogFile("Check if Aadhar number is exactly 12 digits and all characters are numeric");
    if (Aadhar.length() != 12) {
        cout << "Aadhar must be exactly 12 digits long.\n";
        LogFile("Invalid value added, retry.");
        return false;
    }
    for (char c : Aadhar) {
        if (!isdigit(c)) {
            cout << "Aadhar must contain only digits.\n";
            LogFile("Invalid value added, retry.");
            return false;
        }
    }
    SR* ptr = start;
    while (ptr != nullptr) {
        if (ptr->Aadhar == Aadhar) {
            cout << "Aadhar already exists. Insertion failed.\n";
            LogFile("Invalid value added, retry.");
            return false;
        }
        ptr = ptr->next;
    }
    LogFile("Aadhar Prompt is added.");
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
        LogFile("Check If Name is prompted correctly");
        cout << "\nName: "; getline(cin, ptr->name);
    } while (!STRValidity(ptr->name));
    do {
        LogFile("Check If Gender is prompted correctly");
        cout << "\nGender (M/F): ";
        cin.getline(ptr->gender, 3); // Allow space for the null terminator
    } while (ptr->gender[0] != 'M' && ptr->gender[0] != 'F' && ptr->gender[0] != 'm' && ptr->gender[0] != 'f');

    do {
        LogFile("Check If Father Name is prompted correctly"); 
        cout << "\nFather Name: "; getline(cin, ptr->Father_Name);
    } while (!STRValidity(ptr->Father_Name));


    do {
        LogFile("Check if Mother Name is Prompted correctly");
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
    LogFile("Entering Aadhar Number");
    string Aadhar;
    cout << "\nAadhar Number (12 digits): "; getline(cin,Aadhar);
    if (!VerifyAadhar(start, Aadhar))
        return;

    SR* SocietyResident = new SR;
    SocietyResident->Aadhar = Aadhar;
    SocietyResident->next = nullptr;
    SocietyResident->prev = nullptr;

    InputDetails(SocietyResident);

    if (start == NULL) {
        start = SocietyResident;
        LogFile("List was Empty");
    }
    else {
        LogFile("New node has been attached to it's consecutive nodes.");
        SR* ptr = start;
        while (ptr->next != NULL) {
            ptr = ptr->next;
        }
        ptr->next = SocietyResident;
        SocietyResident->prev = ptr;
    }
    cout << "Resident Record Added." << endl;
    LogFile( "Resident Record Added." );
}

void DeleteRecord(SR*&start,const string& Aadhar)
{

    if (start==NULL)
    {
        LogFile("List is Empty. UnderFlow observed.");
        cout<<"List is Empty. UnderFlow observed."<<endl;
        return;
    }
    SR*ptr=start;
    while (ptr!=NULL)
    {
        if (ptr->Aadhar==Aadhar)
        {
            //check if it's not first
            if(ptr->prev!=NULL){
                LogFile("Assigning previous node to the node's next.");
                ptr->prev->next=ptr->next;

            }
            else
                LogFile("Starting node is assigned to the node's next");
                start=ptr->next;
            if (ptr->next!=NULL)
            {
                LogFile("Assigning next node to the node's previous.");
                ptr->next->prev=ptr->prev;
            }
            
            delete ptr;
            LogFile("Resident Record Deleted Successfully.");
            cout<<"Resident Record Deleted."<<endl;
            return;
        }
        LogFile("traverse to next node.");
        ptr=ptr->next;
    }
}

int main() {
    int z;
    LogFile("Starting Program.");
    SR* ptr = NULL;
    while (true) {
        cout << "ABC SOCIETY RESIDENT RECORD DATABASE MANAGER" << endl;
        cout << "Choose a Command:\n1. Insert a Record \n2. Delete a Record  \n3. Update a Record \n4. Keep the Records in sorted order\n5. Find a Record\n6. QUIT PROGRAM\n";
        cin >> z;
        switch (z) {
        case 1:
        LogFile("Insert a Resident Record.");
            InsertRecord(ptr);
            break;
        case 2:
            LogFile("Delete a Resident Record:");
            {
                string Aadhar;
                cin.ignore();
                cout<<"Enter the Aadhar No. of the Required resident record.";
                getline(cin,Aadhar);
                DeleteRecord(ptr,Aadhar);
            }
        case 6:
            LogFile("Closing Society Resident Database Manager.");
            return 0;
        default:
            cout << "Invalid Option. Please choose again." << endl;
            LogFile("Program closed abruptly due to error.");
            break;
        }
    }
}
