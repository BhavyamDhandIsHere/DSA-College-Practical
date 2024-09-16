#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <cctype> // For isdigit function
#include <ctime>
using namespace std;

void LogEvent(const string& event) {
    ofstream logfile("society_log.txt", ios_base::app); // Open in append mode
    if (logfile.is_open()) {
        time_t now = time(0);
        char* dt = ctime(&now); // Convert to string format
        logfile << dt << " : " << event << endl;
        logfile.close();
    } else {
        cout << "Error opening log file!" << endl;
    }
}

struct dateOfBirth {
    int day, year, month;
};
struct Society_Record {
    long long int Aadhar; 
    string name;
    string gender;
    string Father_Name;
    string Mother_Name;
    dateOfBirth DOB;

    Society_Record* prev;
    Society_Record* next;
};

typedef Society_Record SR;

SR* pointToNode(SR* start,long long int Aadhar) {
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
bool VerifyAadhar(SR*& start, const long long int& Aadhar) {
    if (Aadhar < 100000000000 || Aadhar > 999999999999)
    {
        cout<<"Aadhar No. must be 12 digits long:"<<endl;
        return false;
    }
    
    SR* ptr = start;
    while (ptr != nullptr) {
        if (ptr->Aadhar == Aadhar) {
            cout << "Aadhar No. already exists. Insertion failed.\n";
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
        cout << "\nGender (male/female/other): ";
        getline(cin,ptr->gender); // Allow space for the null terminator
    } while (ptr->gender!="male"&&ptr->gender!="female"&&ptr->gender!="other");

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
    long long int Aadhar;
    cout << "\nAadhar No. Number (12 digits): "; cin>>Aadhar;
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
    LogEvent("Inserted record for Aadhar No.: " + to_string(Aadhar));
}
void DeleteRecord(SR*& start, const long long int& Aadhar) {
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
            LogEvent("Deleted record for Aadhar No.: " + to_string(Aadhar));
            return;
        }
        ptr = ptr->next;
    }
}
void updateRecord(SR*& start, const long long int& Aadhar) {
    SR* ptr = pointToNode(start, Aadhar);

    if (ptr == nullptr) {
        cout << "Record Not Found!" << endl;
        return;
    }
    cin.ignore();
    cout << "Updating Record for Aadhar No.: " << Aadhar << endl;
    InputDetails(ptr);

    cout << "Resident Record updated." << endl;
    LogEvent("Updated record for Aadhar No.: " + to_string(Aadhar));
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

    LogEvent("Sorted the records by name.");
}
void FindRecord(SR*ptr)
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
    cout<<"------------------------------------------------"<<endl;

}
void PrintDatabase(SR*start)
{
    cout<<"Printing The Database: "<<endl;
    SR*ptr=start;
    while (ptr!=NULL)
    {
        FindRecord(ptr);
        ptr=ptr->next;
    }
    
}
void GenerateReport(SR*start)
{
    SR*ptr=start;
    if (ptr==NULL)
    {
        cout<<"Database is empty."<<endl;
        return;
    }
    
    int t;
    cout<<"Generate Report from\n\t1.Aadhar Card or\n\t2.Name"<<endl;
    cin>>t;
    cin.ignore();
    switch (t)
    {
    case 1:
        {
            long long int AA;
            cout<<"Enter Aadhar No.: "; cin>>AA;
            ptr=pointToNode(ptr,AA);
            cout<<"REPORT OF RESIDENT WITH AADHAR NO.: "<<ptr->Aadhar<<endl;
            cout<<"------------------------------------------------"<<endl;
            cout<<"Resident Name: "<<ptr->name<<endl;
            cout<<"Father's name: "<<ptr->Father_Name<<endl;
            cout<<"Mother's name: "<<ptr->Mother_Name<<endl;
            cout<<"gender: "<<ptr->gender<<endl;
            cout<<"Date Of Birth: "<<ptr->DOB.day<<"-"<<ptr->DOB.month<<"-"<<ptr->DOB.year<<endl;
            cout<<"------------------------------------------------"<<endl;
            LogEvent("Generated report for Aadhar No.: " + to_string(ptr->Aadhar));
        }
        break;
    case 2:
        {
            string name;
            cout<<"Enter Name:"; getline(cin,name);
            while (ptr!=NULL)
            {
                if (ptr->name==name)
                    break;
                ptr=ptr->next;
            }
            cout<<"REPORT OF RESIDENT WITH NAME: "<<ptr->name<<endl;
            cout<<"------------------------------------------------"<<endl;
            cout<<"Father's name: "<<ptr->Father_Name<<endl;
            cout<<"gender: "<<ptr->gender<<endl;
            cout<<"------------------------------------------------"<<endl;
            LogEvent("Generated report for resident named: " + ptr->name);
        }
        break;
    default:
        cout<<"Invalid Case:"<<endl;
        break;
    }
}
void FreeMemory(SR*&start)
{
    SR*ptr;
    while (start!=nullptr)
    {
        ptr=start;
        start=start->next;
        delete ptr;
    }
    // Log event
    LogEvent("Freed all allocated memory and exited the program.");
}

int main() {
    int z;
    SR* ptr = NULL;
    while (true) {
        cout << "\n\n\t--------------------------------------\n\t    SOCIETY RESIDENT DATABASE\n\t--------------------------------------" << endl;
        cout << "1. Insert a Record" << endl;
        cout << "2. Delete a Record" << endl;
        cout << "3. Update a Record" << endl;
        cout << "4. Sort Records" << endl;
        cout << "5. Find a Record & Print the Database" << endl;
        cout << "6. Generate Report for One Member" << endl;
        cout << "7. Quit Program" << endl;
        cout << "Please Enter your choice (1-7): ";        cin >> z;
        cin.ignore();
        switch (z) {
        case 1:
            InsertRecord(ptr);
            break;
        case 2:
            {
                long long int Aadhar;
                cout << "Enter the Aadhar No. of the Required resident record.";
                cin>>Aadhar;
                DeleteRecord(ptr, Aadhar);
            }
            break;
        case 3:
            {
                long long int Aadhar;
                cout<<"Enter Aadhar No. to Update credentials: "; cin>>Aadhar;
                updateRecord(ptr,Aadhar);
            }
            break;
        case 4:
            PrintDatabase(ptr);
            SortRecords(ptr);
            PrintDatabase(ptr);
            break;
        case 5:
            {
                long long int Aadhar;
                cout<<"Enter Aadhar No. to Print the Credentials: ";cin>>Aadhar;
                cin.ignore();
                FindRecord(pointToNode(ptr,Aadhar));
            }
            break;
        case 6:
            GenerateReport(ptr);
            break;
        case 7:
            FreeMemory(ptr);
            return 0;
        default:
            cout << "Invalid Option. Please choose again." << endl;
            break;
        }
    }
}