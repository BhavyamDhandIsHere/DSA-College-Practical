#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool YearValidity(int year)
{
    if(year > 2024 || year < 2002)
        return false;
    else
        return true;
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

struct subject {
    int sem, year;
    string SubCode;
    string SubTitle;
    int MaxSessional, MaxTheory;
    int SMarks, TMarks;
};

struct dateOfBirth {
    int day, year, month;
};

struct student {
    int En_no, AdYear;
    string AdSem;
    string name;
    string father_name;
    dateOfBirth DOB;
    subject SUB;

    student* prev;
    student* next;
};

typedef student S;

bool EnrollmentValidity(S*& start, int id) {
    if (id < 100000 || id > 999999) {
        cout << "Enrollment No. is Out of Bounds!\n";
        return false;
    }
    S* ptr = start;
    while (ptr != nullptr) {
        if (ptr->En_no == id) {
            cout << "Enrollment No. already exists. Insertion failed.\n";
            return false;
        }
        ptr = ptr->next;
    }
    return true;
}

bool STRValidity(string str) {
    for (char c : str) {
        if (!isalpha(c) && c != '.' && c != ' ') return false;
    }
    return true;
}

S* searchRecord(S* start, int enrollment) {
    S* ptr = start;
    while (ptr != nullptr) {
        if (ptr->En_no == enrollment)
            return ptr;
        ptr = ptr->next;
    }
    return nullptr;
}

// Function Prototypes

void addRecord(S*& start) {
    int Enroll;
    cout << "Adding a New Record... " << endl;
    cout << "\nEnter Enrollment No.: ";
    do
    {
        cin >> Enroll;
    } while (!EnrollmentValidity(start, Enroll));
    
    S* ptr = new S;
    ptr->En_no = Enroll;
    ptr->next = nullptr;
    ptr->prev = nullptr;

    cin.ignore();
    do
    {
        cout << "Enter Name: "; getline(cin, ptr->name);
    } while (!STRValidity(ptr->name));
    do
    {
        cout << "Enter Father's Name: "; getline(cin, ptr->father_name);
    } while (!STRValidity(ptr->father_name));
    do
    {
        cout << "Enter Semester and Year of Admission: \n\tSem of Admission(July/January):"; getline(cin, ptr->AdSem);
    } while (ptr->AdSem != "July" && ptr->AdSem != "January");
    do
    {
        cout << "\n\tyear of admission:  "; cin >> ptr->AdYear;
    } while (!YearValidity(ptr->AdYear));
    while (true)
    {
        cout << "Enter Date of Birth (DD MM YYYY): ";
        cout << "\n\tDay: "; cin >> ptr->DOB.day;
        cout << "\n\tMonth: "; cin >> ptr->DOB.month;
        cout << "\n\tYear: "; cin >> ptr->DOB.year;
        if (DATEValidity(ptr->DOB.day, ptr->DOB.month, ptr->DOB.year))
            break;
        else
            cout << "try again." << endl;
    }
    
    cin.ignore();
    cout << "\nEnter Subject Details: ";

    cout << "\n\tSemester of Subject: "; cin >> ptr->SUB.sem;
    cout << "\n\t Year of Subject: "; cin >> ptr->SUB.year;

    
    cin.ignore();
    cout << "\n\tSubject Code: "; getline(cin, ptr->SUB.SubCode);
    cout << "\n\tSubject Title: "; getline(cin, ptr->SUB.SubTitle);
    cout << "\n\t Max Marks for Sessional: "; cin >> ptr->SUB.MaxSessional;
    cout << "\n\t Max Marks for Theory: "; cin >> ptr->SUB.MaxTheory;
    cout << "\n\t Marks Awarded in Sessional: "; cin >> ptr->SUB.SMarks;
    cout << "\n\t Marks Awarded in Theory: "; cin >> ptr->SUB.TMarks;

    if (start == nullptr) {
        start = ptr;
    } else {
        S* prev = start;
        while (prev->next != nullptr) {
            prev = prev->next;
        }
        prev->next = ptr;
        ptr->prev = prev;
    }
}

void deleteRecord(S*& start, int enrollment) {
    S* ptr = searchRecord(start, enrollment);
    if (ptr == nullptr) {
        cout << "Record not found!" << endl;
        return;
    }

    if (ptr->prev != nullptr)
        ptr->prev->next = ptr->next;
    else
        start = ptr->next;

    if (ptr->next != nullptr)
        ptr->next->prev = ptr->prev;

    delete ptr;
    cout << "Record deleted successfully!" << endl;
}

void updateRecord(S* start, int enrollment) {
    S* ptr = searchRecord(start, enrollment);
    if (ptr == nullptr) {
        cout << "Record not found!" << endl;
        return;
    }

    cin.ignore();
    do
    {
        cout << "Enter Name: "; getline(cin, ptr->name);
    } while (!STRValidity(ptr->name));
    do
    {
        cout << "Enter Father's Name: "; getline(cin, ptr->father_name);
    } while (!STRValidity(ptr->father_name));
    do
    {
        cout << "Enter Semester and Year of Admission: \n\tSem of Admission(July/January):"; getline(cin, ptr->AdSem);
    } while (ptr->AdSem != "July" && ptr->AdSem != "January");
    do
    {
        cout << "\n\tyear of admission:  "; cin >> ptr->AdYear;
    } while (!YearValidity(ptr->AdYear));
    while (true)
    {
        cout << "Enter Date of Birth (DD MM YYYY): ";
        cout << "\n\tDay: "; cin >> ptr->DOB.day;
        cout << "\n\tMonth: "; cin >> ptr->DOB.month;
        cout << "\n\tYear: "; cin >> ptr->DOB.year;
        if (DATEValidity(ptr->DOB.day, ptr->DOB.month, ptr->DOB.year))
            break;
        else
            cout << "try again." << endl;
    }
    
    cin.ignore();
    cout << "\nEnter Subject Details: ";

    cout << "\n\tSemester of Subject: "; cin >> ptr->SUB.sem;
    cout << "\n\t Year of Subject: "; cin >> ptr->SUB.year;

    
    cin.ignore();
    cout << "\n\tSubject Code: "; getline(cin, ptr->SUB.SubCode);
    cout << "\n\tSubject Title: "; getline(cin, ptr->SUB.SubTitle);
    cout << "\n\t Max Marks for Sessional: "; cin >> ptr->SUB.MaxSessional;
    cout << "\n\t Max Marks for Theory: "; cin >> ptr->SUB.MaxTheory;
    cout << "\n\t Marks Awarded in Sessional: "; cin >> ptr->SUB.SMarks;
    cout << "\n\t Marks Awarded in Theory: "; cin >> ptr->SUB.TMarks;

    cout << "Record updated successfully!" << endl;
}

void printReportCard(S* student) {
    if (student == nullptr) {
        cout << "Record not found!" << endl;
        return;
    }

    cout << "Report Card for " << student->name << endl;
    cout << "Enrollment No.: " << student->En_no << endl;
    cout << "Father's Name: " << student->father_name << endl;
    cout << "Date of Birth: " << student->DOB.day << "-" << student->DOB.month << "-" << student->DOB.year << endl;
    cout << "Semester of Admission: " << student->AdSem << endl;
    cout << "Year of Admission: " << student->AdYear << endl;
    cout << "Subject Details:" << endl;
    cout << "Semester: " << student->SUB.sem << ", Year: " << student->SUB.year << endl;
    cout << "Subject Code: " << student->SUB.SubCode << ", Title: " << student->SUB.SubTitle << endl;
    cout << "Max Sessional Marks: " << student->SUB.MaxSessional << ", Awarded: " << student->SUB.SMarks << endl;
    cout << "Max Theory Marks: " << student->SUB.MaxTheory << ", Awarded: " << student->SUB.TMarks << endl;
}

void printSemesterResults(S* start, int semester, int year) {
    S* ptr = start;
    cout << "Results for Semester " << semester << ", Year " << year << endl;
    while (ptr != nullptr) {
        if (ptr->SUB.sem == semester && ptr->SUB.year == year) {
            cout << "Enrollment No.: " << ptr->En_no << ", Name: " << ptr->name << endl;
            cout << "Subject Code: " << ptr->SUB.SubCode << ", Title: " << ptr->SUB.SubTitle << endl;
            cout << "Max Sessional Marks: " << ptr->SUB.MaxSessional << ", Awarded: " << ptr->SUB.SMarks << endl;
            cout << "Max Theory Marks: " << ptr->SUB.MaxTheory << ", Awarded: " << ptr->SUB.TMarks << endl;
            cout << "-----------------------------" << endl;
        }
        ptr = ptr->next;
    }
}

void sortRecords(S*& start) {
    if (start == nullptr) return;

    bool swapped;
    do {
        swapped = false;
        S* ptr = start;
        while (ptr->next != nullptr) {
            if (ptr->name > ptr->next->name) {
                swap(ptr->name, ptr->next->name);
                swap(ptr->En_no, ptr->next->En_no);
                swap(ptr->father_name, ptr->next->father_name);
                swap(ptr->DOB, ptr->next->DOB);
                swap(ptr->AdSem, ptr->next->AdSem);
                swap(ptr->AdYear, ptr->next->AdYear);
                swap(ptr->SUB, ptr->next->SUB);
                swapped = true;
            }
            ptr = ptr->next;
        }
    } while (swapped);
    cout << "Records sorted successfully!" << endl;
}
void saveToFile(S* start) {
    ofstream file("students.txt");
    S* ptr = start;
    while (ptr != nullptr) {
        file << ptr->En_no << endl;
        file << ptr->name << endl;
        file << ptr->father_name << endl;
        file << ptr->AdSem << endl;
        file << ptr->AdYear << endl;
        file << ptr->DOB.day << " " << ptr->DOB.month << " " << ptr->DOB.year << endl;
        file << ptr->SUB.sem << " " << ptr->SUB.year << endl;
        file << ptr->SUB.SubCode << endl;
        file << ptr->SUB.SubTitle << endl;
        file << ptr->SUB.MaxSessional << endl;
        file << ptr->SUB.MaxTheory << endl;
        file << ptr->SUB.SMarks << endl;
        file << ptr->SUB.TMarks << endl;
        ptr = ptr->next;
    }
    file.close();
    cout << "Data saved to text file successfully!" << endl;
}
void loadFromFile(S*& start) {
    ifstream file("students.txt");
    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }

    while (!file.eof()) {
        S* ptr = new S;
        file >> ptr->En_no;
        file.ignore(); // ignore newline character after En_no

        getline(file, ptr->name);
        getline(file, ptr->father_name);
        getline(file, ptr->AdSem);
        file >> ptr->AdYear;
        file.ignore(); // ignore newline character after AdYear

        file >> ptr->DOB.day >> ptr->DOB.month >> ptr->DOB.year;
        file >> ptr->SUB.sem >> ptr->SUB.year;
        file.ignore(); // ignore newline character after SUB.year

        getline(file, ptr->SUB.SubCode);
        getline(file, ptr->SUB.SubTitle);
        file >> ptr->SUB.MaxSessional;
        file >> ptr->SUB.MaxTheory;
        file >> ptr->SUB.SMarks;
        file >> ptr->SUB.TMarks;
        file.ignore(); // ignore newline character after TMarks

        ptr->next = nullptr;
        ptr->prev = nullptr;

        if (start == nullptr) {
            start = ptr;
        } else {
            S* last = start;
            while (last->next != nullptr) {
                last = last->next;
            }
            last->next = ptr;
            ptr->prev = last;
        }
    }

    file.close();
    cout << "Data loaded from file successfully!" << endl;
}

int main() {
    S* start = nullptr;
    loadFromFile(start);
    int choice, enrollment, semester, year;

    while (true) {
        cout << "\n1. Add Record\n2. Delete Record\n3. Update Record\n4. Print Report Card\n5. Print Semester Results\n6. Sort Records\n7. Save to File\n8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addRecord(start);
                break;
            case 2:
                cout << "Enter Enrollment Number to Delete: ";
                cin >> enrollment;
                deleteRecord(start, enrollment);
                break;
            case 3:
                cout << "Enter Enrollment Number to Update: ";
                cin >> enrollment;
                updateRecord(start, enrollment);
                break;
            case 4:
                cout << "Enter Enrollment Number to Print Report Card: ";
                cin >> enrollment;
                printReportCard(searchRecord(start, enrollment));
                break;
            case 5:
                cout << "Enter Semester and Year to Print Results: ";
                cin >> semester >> year;
                printSemesterResults(start, semester, year);
                break;
            case 6:
                sortRecords(start);
                break;
            case 7:
                saveToFile(start);
                break;
            case 8:
                return 0;
            default:
                cout << "Invalid choice, please try again!" << endl;
        }
    }

    return 0;
}
