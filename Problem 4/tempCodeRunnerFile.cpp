#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <cctype> // For isdigit function
using namespace std;

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