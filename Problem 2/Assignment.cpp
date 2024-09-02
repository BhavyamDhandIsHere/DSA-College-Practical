#include <iostream>
#include <cstring>
using namespace std;
const int MAX=5;
struct Address {
    string House_No;
    string street_name;
    string City;
    string state;
    string Country;
};
struct DOB {
    string date;
    string month;
    string year;
};
struct Biodata {
    string Roll_no;
    string Student;
    string Father;
    string Mother;
    string YearOfAdmission;
    DOB day;
    string Class;
    string Semester;
    string branch;
    Address add;
};
void input_record(Biodata B[], int &n) {
    if (n >= MAX) {
        cout<<"Maximum limit reached. Cannot add more entries"<<endl;
        return;
    }
    cin.ignore(); // Clear the input buffer
    while (true) {
        cout <<"Roll No.: ";
        getline(cin, B[n].Roll_no);
        // Check for duplicity
        bool duplicate = false;
        for (int i = 0; i < n; i++) {
            if (B[n].Roll_no == B[i].Roll_no) {
                cout <<"ERROR! Duplicity found in Index "<<i<<"!"<<endl;
                duplicate = true;
                break;
            }
        }
        if (!duplicate) {
            break;
        } else {
            cout<<"Please enter a different Roll No."<<endl;
        }
    }
    cout<<"Year of Admission: "; getline(cin, B[n].YearOfAdmission);
    cout<<"Date Of Birth:\n\tDay: "; getline(cin, B[n].day.date);
    cout<<"\tMonth: "; getline(cin, B[n].day.month);
    cout<<"\tYear: "; getline(cin, B[n].day.year);
    cout<<"Student Name: "; getline(cin, B[n].Student);
    cout<<"Father Name: "; getline(cin, B[n].Father);
    cout<<"Mother Name: "; getline(cin, B[n].Mother);
    cout<<"Your Class: "; getline(cin, B[n].Class);
    cout<<"Semester: "; getline(cin, B[n].Semester);
    cout<<"Branch: "; getline(cin, B[n].branch);
    cout<<"ADDRESS:\n\tHouse No.: "; getline(cin, B[n].add.House_No);
    cout<<"\tName of Street: "; getline(cin, B[n].add.street_name);
    cout<<"\tCity: "; getline(cin, B[n].add.City);
    cout<<"\tState: "; getline(cin, B[n].add.state);
    cout<<"\tCountry: "; getline(cin, B[n].add.Country);
    n++;
    cout<<"Record Input successful!"<<endl;
}
void print_record(Biodata B[],int i)
{
    cout<<endl;
    cout<<"Record "<<i+1<<":\n";
    cout<<"Roll No.: "<<B[i].Roll_no<<"\n";
    cout<<"Year of Admission: "<<B[i].YearOfAdmission<<"\n";
    cout<<"Date of Birth: "<<B[i].day.date<<"-"<<B[i].day.month<<"-"<<B[i].day.year<<"\n";
    cout<<"Student Name: "<<B[i].Student<<"\n";
    cout<<"Father Name: "<<B[i].Father<<"\n";
    cout<<"Mother Name: "<<B[i].Mother<<"\n";
    cout<<"Class: " <<B[i].Class<<"\n";
    cout<<"Semester: "<<B[i].Semester<<"\n";
    cout<<"Branch: "<<B[i].branch<<"\n";
    cout<<"Address: "<<B[i].add.House_No<<", "<<B[i].add.street_name<<", "<<B[i].add.City<<", "<<B[i].add.state<<", "<<B[i].add.Country<<"\n";
    cout<<endl;

}
void search_record(Biodata B[], int n) {
    cin.ignore();
    bool found=false;
    string roll_no;
    cout<<"Enter the Roll No. you want to search: "; getline(cin,roll_no);
    for (int i = 0; i < n; i++) 
    {
        if (roll_no == B[i].Roll_no) {
            print_record(B,i);
            found=true;
            return;
        }
    }
    cout<<"record Not Found"<<endl;    
}
void delete_record(Biodata B[], int &n, string roll_no) {
    int index = -1;
    for (int i = 0; i < n; i++) {
        if (B[i].Roll_no == roll_no) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        cout<<"record not found!"<<endl;
        return;
    }

    for (int i = index; i < n - 1; i++) {
        B[i] = B[i + 1];
    }
    n--;
    cout << "record deleted successfully!" << endl;
}
void display_record(Biodata B[], int n) {
    if (n != 0) 
    {
        int z;
        string city,State,Country;
        cin.ignore();
        cout<<"Display Entries based on:\n 1:City Name \n2:State Name \n3:Country Name"<<endl; cin>>z;
        switch (z)
        {
        case 1:
            cin.ignore();
            cout<<"Enter City Name: ";
            getline(cin,city);
            for (int i = 0; i < n; i++) 
            {
                if (city==B[i].add.City)
                {
                    print_record(B,i);
                    continue;
                }               
            }
            break;
        case 2:
            cin.ignore();
            cout<<"Enter State Name: ";
            getline(cin,State);
            for (int i = 0; i < n; i++) 
            {
                if (State==B[i].add.state)
                {
                    print_record(B,i);
                    continue;
                }
            }
            break;
        case 3:
            cin.ignore();
            cout<<"Enter Country Name: ";
            getline(cin,Country);
            for (int i = 0; i < n; i++) 
            {
                if (Country==B[i].add.Country)
                {
                    print_record(B,i);
                    continue;
                }
            }
            break;
        default:
            cout<<"Invalid option: "<<endl;
            break;
        }
    } 
    else 
    {
        cout << "Database is Empty!" << endl;
    }
}
int main() {
    Biodata Group1[MAX];
    int n = 0;
    int x;
    while (true) {
        cout << "\n\nWelcome to the Database manager program!\nEnter your desired choice:\n";
        cout << "1. Input an record\n2. Delete record from Database\n3. Search record from Database\n4. Display Records of a city/State/Country \n5. Quit Program\n";
        cin >> x;
        switch (x) {
            case 1:
                input_record(Group1,n);
                break;
            case 2:
                {
                    string roll_no;
                    cout <<"Enter Roll No. to delete: ";
                    cin >> roll_no;
                    delete_record(Group1,n, roll_no);
                }
                break;
            case 3:
                search_record(Group1,n);
                break;
            case 4:
                display_record(Group1, n);
                break;
            case 5:
                return 0;
            default:
                cout << "Invalid choice." << endl;
                return 0;
                break;
        }
    }
    return 0;
}