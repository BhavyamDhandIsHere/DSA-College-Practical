#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

void write_text_to_log_file( const std::string &text )
{
    std::ofstream log_file(
        "log_file.txt", ios_base::out | ios_base::app );
    log_file << text<<endl;
}


struct address
{
    int House_no,pin;
    char street[20],city[30],state[20],country[20];
};
struct dateOfJoining
{
    int day,year, month;
};

struct Employee {
    int employeeId;
    char employeeName[20];
    char fatherName[20];
    char motherName[20];
    char position[10];
    char department[5];
    dateOfJoining DOJ;
    address ADD;
    Employee* next;
};
typedef Employee E;

bool DATEValidity(int day,int month, int year)
{
    write_text_to_log_file("Checking if Date is Valid or not...");
    if (year<2002||year>2024)
        return false;
    if (year==2024&&month>8&&day>19)
    {
        return false;               
    }
    if (day<1||day>31||month<1||month>12)
        return false;
    if ((month==4||month==6||month==9||month==11)&&day>30)
        return false;
    if (month==2)
    {
        bool leapyear=(year%4==0&&year%100!=0)||(year%400==0);
        if(day>(leapyear?29:28))
            return false;
    }

    return true;
    
}

bool IDValidity(E*& start, int id) {

    write_text_to_log_file("Checking if ID is Valid or not...");
    if (id < 100000 || id > 999999) {
        cout << "ID is Out of Bounds!\n";
        return false;
    }
    E* ptr = start;
    while (ptr != nullptr) {
        if (ptr->employeeId == id) {
            cout << "Employee ID already exists. Insertion failed.\n";
            return false;
        }
        ptr = ptr->next;
    }
    return true;
}

bool STRValidity(char str[],int n) {
    write_text_to_log_file("Checking if String is made of Alphabets or not...");
    char c;
    for (int i = 0; i < n-1; i++)
    {
        c=str[i];
        if (!isalpha(c) && c != '.'&&c!=' ') return false;
    }
    
    return true;
}

void inputDetails(E* ptr) {
    cin.ignore();
    write_text_to_log_file("Entering Name....");
    do {
        cout << "\nName: "; 
        cin.getline(ptr->employeeName, 20);
    } while (!STRValidity(ptr->employeeName,20));

    write_text_to_log_file("Entering Father Name....");
    do {
        cout << "\nFather Name: "; 
        cin.getline(ptr->fatherName, 20);
    } while (!STRValidity(ptr->fatherName,20));

    write_text_to_log_file("Entering Mother Name....");
    do {
        cout << "\nMother Name: "; 
        cin.getline(ptr->motherName, 20);
    } while (!STRValidity(ptr->motherName,20));

    write_text_to_log_file("Entering Position....");
    do {
        cout << "\nPosition: "; 
        cin.getline(ptr->position, 10);
    } while (!STRValidity(ptr->position,10));

    write_text_to_log_file("Entering Department....");
    do {
        cout << "\nDepartment: "; 
        cin.getline(ptr->department, 5);
    } while (!STRValidity(ptr->department,5));

    write_text_to_log_file("Entering Date of Joining....");
    while (true) {
        cout << "\nDate of Joining:\n\tDAY: "; cin >> ptr->DOJ.day;
        cout << "\n\tMonth (1-12): "; cin >> ptr->DOJ.month;
        cout << "\n\tYear: "; cin >> ptr->DOJ.year;
        if (DATEValidity(ptr->DOJ.day, ptr->DOJ.month, ptr->DOJ.year)) break;
        else cout << "Invalid date. Please enter again.\n";
    }

    cout << "\nAddress:\n\tHouse No.(INTEGER ONLY): "; cin >> ptr->ADD.House_no;
    cin.ignore();  // Ignore leftover newline character from previous input

    cout << "\n\tStreet Name: "; 
    cin.getline(ptr->ADD.street, 20);
    
    do {
        cout << "\n\tCity Name: "; 
        cin.getline(ptr->ADD.city, 30);
    } while (!STRValidity(ptr->ADD.city,30));

    do {
        cout << "\n\tState Name: "; 
        cin.getline(ptr->ADD.state, 20);
    } while (!STRValidity(ptr->ADD.state,20));

    do {
        cout << "\n\tCountry Name: "; 
        cin.getline(ptr->ADD.country, 20);
    } while (!STRValidity(ptr->ADD.country,20));

    cout << "\n\tPin Code(INTEGER ONLY): "; cin >> ptr->ADD.pin;
    ptr->next = nullptr;
}


void InsertRecord(E*& start) {
    int id;
    cout << "\nEmployee Id: "; cin >> id;
    if (!IDValidity(start, id)) {
        return;
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
}

void DeleteRecord(E*& start,int id)
{
    if (start==nullptr)
    {
        cout<<"Deletion failed since list is empty.";
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

void SingleEmployee(E* ptr)
{
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

void FindRecord(E* start,int id) {
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
    E*ptr=start;
    cout<<"Display all records belonging to: \n1.City \n2.State \n3.Country \n4.PIN"<<endl;
    int z;
    cin>>z;
    switch (z)
    {
    case 1:
        {
            cin.ignore();
            char city[30];
            cout<<"\nCity: ";cin.getline(city,30);
            while (ptr!=nullptr)
            {
                if (strcmp(ptr->ADD.city,city)==0)
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

            char state[20];
            cout<<"\nstate: ";cin.getline(state,20);
            while (ptr!=nullptr)
            {
                if (strcmp(ptr->ADD.state,state)==0)
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
            char country[20];
            cout<<"\nCountry: ";cin.getline(country,20);
            while (ptr!=nullptr)
            {
                if (strcmp(ptr->ADD.country,country)==0)
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
    write_text_to_log_file("Program Started!\n");
    int z;
    E* start=nullptr;
    while (true)
    {
        cout<<"welcome to the Employee Database. Enter Your Choice:\n1.Insert a Record \n2.Delete a Record \n3.Find a Record \n4.Update a Record \n5.Display the Records of all Employees belonging to a particular City/State/Country/PIN \n6.QUIT PROGRAM"<<endl;
        cin>>z;
        switch (z)
        {
        case 1:
            InsertRecord(start);
            write_text_to_log_file("Initiate Input of Record...");
            break;
        case 2:
            {
                int id;
                cout<<"Enter the ID of Employee you want to Delete: "; cin>>id;cout<<endl;
                DeleteRecord(start,id);
                write_text_to_log_file("Deleting Record of desired ID from Database...");
            }
            break;
        case 3:
            {
                int id;
                cout<<"Enter the ID of Employee you want to Find: "; cin>>id;cout<<endl;
                FindRecord(start,id);
                write_text_to_log_file("Finding Record of desired ID within database...");
            }
            break;
        case 4:
            {
                int id;
                cout<<"Enter the ID of Employee you want to Update: "; cin>>id;cout<<endl;
                UpdateRecord(start,id);
                write_text_to_log_file("Updating Record of desired ID of a database...");
            }
            break;
        case 5:
            DisplayRecords(start);
            write_text_to_log_file("Displaying Records of desired City/state/country within the database...");
            break;
        case 6:
            write_text_to_log_file("Ending Program.");
            return 0;
        default:
            cout<<"Invalid Option."<<endl;
            write_text_to_log_file("Error. Forcing shutdown of Program.");
            return 0;
        }
    }


} 
