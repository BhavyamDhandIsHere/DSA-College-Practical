#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void LogFile(const string &txt)
{
    ofstream log_file("logfile.txt",ios_base::out|ios_base::app);
    log_file<<txt<<endl;
}

struct address
{
    int House_no,pin;
    string street,city,state,country;
};
struct dateOfJoining
{
    int day,year, month;
};

struct Employee {
    int employeeId;
    string employeeName;
    string fatherName;
    string motherName;
    string position;
    string department;
    dateOfJoining DOJ;
    address ADD;
    Employee* next;
};
typedef Employee E;

bool DATEValidity(int day,int month, int year)
{
    LogFile("Check if Date of Joining is Invalid.");
    if (year<2002||year>2024)
        {return false;
        LogFile("Date Invalid.");}
    if (year==2024&&month>8&&day>30)
    {
        return false;
        LogFile("Date Invalid.");               
    }
    if (day<1||day>31||month<1||month>12)
        {return false;
        LogFile("Date Invalid.");}
    if ((month==4||month==6||month==9||month==11)&&day>30)
        {return false;
        LogFile("Date Invalid.");}
    if (month==2)
    {
        bool leapyear=(year%4==0&&year%100!=0)||(year%400==0);
        if(day>(leapyear?29:28))
            {return false;
            LogFile("Date Invalid.");}
    }

    return true;
    LogFile("Date valid.");

}

bool IDValidity(E*& start, int id) {

    LogFile("Check if EmployeeID is Invalid");
    if (id < 100000 || id > 999999) {
        cout << "ID is Out of Bounds!\n";
        return false;
        LogFile("ID Invalid.");

    }
    E* ptr = start;
    while (ptr != nullptr) {
        if (ptr->employeeId == id) {
            cout << "Employee ID already exists. Insertion failed.\n";
            return false;
            LogFile("ID Invalid.");

        }
        ptr = ptr->next;
    }
    return true;
    LogFile("ID Valid.");

}

bool STRValidity(string str) {
    LogFile("Check if String is Alphabetical or not.");
    for (char c : str) {
        if (!isalpha(c) && c != '.'&&c!=' ') return false;
    }
    return true;
}

void SingleEmployee(E* ptr)
{
    LogFile("Printing a Single Employee.");
    cout << "--------------------------\n";
    cout << "Employee ID: " << ptr->employeeId << endl;
    cout << "Name: " << ptr->employeeName << endl;
    cout << "Father Name: " << ptr->fatherName << endl;
    cout << "Mother Name: " << ptr->motherName << endl;
    cout << "Position: " << ptr->position << endl;
    cout << "Department: " << ptr->department << endl;
    cout << "Date of Joining: " << ptr->DOJ.day << " " << ptr->DOJ.month << " " << ptr->DOJ.year << endl;
    cout << "Address: " << ptr->ADD.House_no << ",\nStreet Name:" << ptr->ADD.street << ",\nCity:" << ptr->ADD.city << ",\nState:" << ptr->ADD.state << ",\nCountry:" << ptr->ADD.country << ",\nPIN: " << ptr->ADD.pin << endl;
    cout << "--------------------------\n";

}

void inputDetails(E *ptr) {
    LogFile("Input Details for Employee.");
    cin.ignore();
    do {
        cout << "\nName: "; getline(cin, ptr->employeeName);
    } while (!STRValidity(ptr->employeeName));

    do {
        cout << "\nFather Name: "; getline(cin, ptr->fatherName);
    } while (!STRValidity(ptr->fatherName));

    do {
        cout << "\nMother Name: "; getline(cin, ptr->motherName);
    } while (!STRValidity(ptr->motherName));

    do {
        cout << "\nPosition: "; getline(cin, ptr->position);
    } while (!STRValidity(ptr->position));

    do {
        cout << "\nDepartment: "; getline(cin, ptr->department);
    } while (!STRValidity(ptr->department));

    while (true) {
        cout << "\nDate of Joining:\n\tDAY: "; cin >> ptr->DOJ.day;
        cout << "\n\tMonth (1-12): "; cin >> ptr->DOJ.month;
        cout << "\n\tYear: "; cin >> ptr->DOJ.year;
        if (DATEValidity(ptr->DOJ.day, ptr->DOJ.month, ptr->DOJ.year)) break;
        else cout << "Invalid date. Please enter again.\n";
    }

    cout << "\nAddress:\n\tHouse No.(INTEGER ONLY): "; cin >> ptr->ADD.House_no;
    cin.ignore();
    cout << "\n\tStreet Name: "; getline(cin, ptr->ADD.street);
    do {
        cout << "\n\tCity Name: "; getline(cin, ptr->ADD.city);
    } while (!STRValidity(ptr->ADD.city));

    do {
        cout << "\n\tState Name: "; getline(cin, ptr->ADD.state);
    } while (!STRValidity(ptr->ADD.state));

    do {
        cout << "\n\tCountry Name: "; getline(cin, ptr->ADD.country);
    } while (!STRValidity(ptr->ADD.country));

    cout << "\n\tPin Code(INTEGER ONLY): "; cin >> ptr->ADD.pin;
    ptr->next = nullptr;}


void InsertRecord(E*& start) {
    LogFile("Insert Record for Database");
    int id;
    E*x=start;
    cout << "\nEmployee Id: "; cin >> id;
    
    if (!IDValidity(start, id)) {
        return;
    }
    while (x!=nullptr)
    {
        if (x->employeeId==id)
        {
            cout << "Error: Duplicate Employee ID detected. Insertion failed.\n";
            LogFile("ID is duplicate");
            return; 
        }
        x = x->next;
    }

    E* newEmployee = new E;
    newEmployee->employeeId = id;
    inputDetails(newEmployee);

    if (start == nullptr) {
        start = newEmployee;
    } else {
        E* ptr = start;
        while (ptr->next != nullptr) {
            ptr = ptr->next;
        }
        ptr->next = newEmployee;
    }
    cout << "Employee inserted successfully.\n";
    LogFile("Employee inserted successfully.");
}

void DeleteRecord(E*& start,int id)
{
    LogFile("Deleting Record.");
    if (start==nullptr)
    {
        cout<<"Deletion failed since list is empty.";
        LogFile("List is Empty");
        return;
    }
    E*ptr=start;
    E*prev=nullptr;
    while (ptr!=nullptr&&ptr->employeeId!=id)
    {
        prev=ptr;
        ptr=ptr->next;
    }
    if (ptr == nullptr) {
        cout << "Employee ID not found, deletion failed.\n";
        return;
    }

    if (prev == nullptr) {
        start = ptr->next;
    } else {
        prev->next = ptr->next;
    }

    delete ptr;
    cout << "Employee deleted successfully.\n";    
}


void FindRecord(E* start,int id) {
    LogFile("Finding Record.");
    E* ptr = start;
    while (ptr != nullptr) {
        if (ptr->employeeId==id)
        {
            SingleEmployee(ptr);
            return;
        }
        
        ptr = ptr->next;
    }
    cout<<"Employee ID Not Found."<<endl;
}

void UpdateRecord(E* start,int id)
{
    LogFile("Updating Record.");
    E*ptr=start;
    while (ptr!=nullptr)
    {
        if (ptr->employeeId==id)
        {
            cout<<"Update the entire Record under the ID: "<<ptr->employeeId;
            inputDetails(ptr);
            return;
        }
        ptr=ptr->next;
    }
    cout<<"Employee ID Not Found."<<endl;
}

void DisplayRecords(E*start)
{
    LogFile("Displaying Record.");
    E*ptr=start;
    cout<<"Display all records belonging to: \n1.City \n2.State \n3.Country \n4.PIN"<<endl;
    int z;
    cin>>z;
    switch (z)
    {
    case 1:
        {
            cin.ignore();
            string city;
            cout<<"\nCity: ";getline(cin,city);
            while (ptr!=nullptr)
            {
                if (ptr->ADD.city==city)
                {
                    SingleEmployee(ptr);
                }
                ptr=ptr->next;
            }
        }
        cout<<"Employee ID Not Found."<<endl;
        break;
    case 2:
        {
            cin.ignore();

            string state;
            cout<<"\nstate: ";getline(cin,state);
            while (ptr!=nullptr)
            {
                if (ptr->ADD.state==state)
                {
                    SingleEmployee(ptr);
                }
                ptr=ptr->next;
            }
        }
        cout<<"Employee ID Not Found."<<endl;
        break;
    case 3:
        {
            cin.ignore();
            string country;
            cout<<"\nCountry: ";getline(cin,country);
            while (ptr!=nullptr)
            {
                if (ptr->ADD.country==country)
                {
                    SingleEmployee(ptr);
                }
                ptr=ptr->next;
            }
            
        }
        cout<<"Employee ID Not Found."<<endl;
        break;
    case 4:
        {
            cin.ignore();
            int PIN;
            cout<<"\nPIN: ";cin>>PIN;
            while (ptr!=nullptr)
            {
                if (ptr->ADD.pin==PIN)
                {
                    SingleEmployee(ptr);
                }
                ptr=ptr->next;            
            }
        }
        cout<<"Employee ID Not Found."<<endl;
        break;
    default:
        cout<<"Invalid Choice."<<endl;
        break;
    }
}

int main()
{
    LogFile("Starting program.");
    int z;
    E* start=nullptr;
    while (true)
    {
        cout<<"welcome to the Employee Database. Enter Your Choice:\n1.Insert a Record \n2.Delete a Record \n3.Find a Record \n4.Update a Record \n5.Display the Records of all Employees belonging to a particular City/State/Country/PIN \n6.QUIT PROGRAM"<<endl;
        cin>>z;
        switch (z)
        {
        case 1:
            LogFile("Chose InsertRecord");
            InsertRecord(start);
            break;
        case 2:
            {
                LogFile("Chose DeleteRecord");
                int id;
                cout<<"Enter the ID of Employee you want to Delete: "; cin>>id;cout<<endl;
                DeleteRecord(start,id);
            }
            break;
        case 3:
            {LogFile("Chose FindRecord");
                int id;
                cout<<"Enter the ID of Employee you want to Find: "; cin>>id;cout<<endl;
                FindRecord(start,id);}
            break;
        case 4:
            {LogFile("Chose UpdateRecord");
                int id;
                cout<<"Enter the ID of Employee you want to Update: "; cin>>id;cout<<endl;
                UpdateRecord(start,id);}
            break;
        case 5:
            LogFile("Chose DisplayRecord");
            DisplayRecords(start);
            break;
        case 6:
            LogFile("Closing Program.");
            return 0;
        default:
            cout<<"Invalid Option."<<endl;
            return 0;
        }
    }
    

}
