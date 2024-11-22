#include <bits/stdc++.h>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
//to depict empty entries as empty
#define EMPTY -1
#define DELETED -2
//function to verify name is alphabetical
bool VerifyName(string name) {
    for (char c : name) {
        if (!isalpha(c) && c != '.' && c != ' ') return false;
    }
    return true;
}

struct EmployeeHashNode {
    int key;
    string name;
    string gender;
    string mobile;
    string email;
    string qualifications;
    bool occupied;
    // Constructor to initialize an empty node
    EmployeeHashNode() : key(EMPTY), name(""), gender(""), mobile(""), email(""), qualifications(""), occupied(false) {}
    //Function to input Node data
    void Input(int Key) {
        this->key = Key;
        do {
            cout << "Enter name: ";
            getline(cin, name);
        } while (!VerifyName(name));
        cout << "Enter gender: ";
        getline(cin, gender);
        cout << "Enter Phone Number: ";
        getline(cin, mobile);
        cout << "Enter Email-id: ";
        getline(cin, email);
        cout << "Enter Qualifications: ";
        getline(cin, qualifications);
        occupied = true;
    }
    //function which displays Node Data
    void Display() const {
        if (occupied) {
            cout << "Key: " << key << "  Name: " << name
                 << "  Gender: " << gender
                 << "  Mobile: " << mobile << "  Email: " << email
                 << "  Qualifications: " << qualifications << endl;
        } else {
            cout <<" Empty" << endl;
        }
    }
};
//Datatype which depicts HashTable
struct HashTable {
    vector<EmployeeHashNode> Table;
    int M;

    HashTable(int MaxSize) : M(MaxSize) {
        Table.resize(MaxSize);
    }
};

// Hash function to compute the index
int HashFunction(int key, int M) {
    return key % M;  // Simple modulus hash function
}

// Insert a node into the hash table
void insert(HashTable& H, const EmployeeHashNode& Node) {
    int index = HashFunction(Node.key, H.M);
    int OGIndex = index;
    while (H.Table[index].occupied && (H.Table[index].key != EMPTY && H.Table[index].key != DELETED)) {
        index = (index + 1) % H.M;
        if (index == OGIndex) {
            cout << "Hash table is full!\n";
            return;
        }
    }
    H.Table[index] = Node;
}

// Delete a node from the hash table
void Delete(HashTable& H, int key) {
    int index = HashFunction(key, H.M);
    int originalIndex = index;

    while (H.Table[index].occupied) {
        if (H.Table[index].key == key) {
            H.Table[index] = EmployeeHashNode();
            H.Table[index].key = DELETED;
            cout << "Deleted employee with key: " << key << "\n";
            return;
        }
        index = (index + 1) % H.M;
        if (index == originalIndex)
            break;
    }
    cout << "Employee with key " << key << " not found.\n";
}

// Search for a node by key in the hash table
void Search(const HashTable& H, int key) {
    int index = HashFunction(key, H.M);
    int OGindex = index;
    while (H.Table[index].occupied) {
        if (H.Table[index].key == key) {
            cout << "Employee found:\n";
            H.Table[index].Display();
            return;
        }
        index = (index + 1) % H.M;
        if (index == OGindex)
            break;
    }
    cout << "Employee not found.\n";
}

// Display all nodes in the hash table
void Display(const HashTable& H) {
    for (int i = 0; i < H.M; ++i) {
            cout << "Index " << i << ": ";
            H.Table[i].Display();
    }
}

// Update the details of an employee
void Update(HashTable& H, int key) {
    int index = HashFunction(key, H.M);
    int originalIndex = index;
    cin.ignore();

    while (H.Table[index].occupied) {
        if (H.Table[index].key == key) {
            cout << "Employee found. Enter new details:\n";
            H.Table[index].Input(key);
            cout << "Employee details updated successfully.\n";
            return;
        }
        index = (index + 1) % H.M;
        if (index == originalIndex)
            break;
    }
    cout << "Employee with key " << key << " not found.\n";
}
//load data from emp.dat file
void LoadFromFile(HashTable& H, const string& filename) {
    ifstream infile(filename);

    if (!infile) {
        cout << "Error opening file: " << filename << endl;
        return;
    }

    string name, gender, mobile, email, qualifications;
    int key;

    while (infile >> key) {
        // Skip the newline character after the key
        infile.ignore();

        // Read the name, gender, mobile, email, and qualifications
        getline(infile, name, ' ');  // Read until the first space for name
        getline(infile, gender, ' '); // Read until the next space for gender
        getline(infile, mobile, ' '); // Read until the next space for mobile
        getline(infile, email, ' ');  // Read until the next space for email
        getline(infile, qualifications); // Read the rest for qualifications

        // Create an EmployeeHashNode with the parsed data
        EmployeeHashNode Node;
        Node.key = key;
        Node.name = name;
        Node.gender = gender;
        Node.mobile = mobile;
        Node.email = email;
        Node.qualifications = qualifications;
        Node.occupied = true;

        // Insert the node into the hash table
        insert(H, Node);
    }
    infile.close();
    cout << "Data loaded from file successfully.\n";
}

//user interface
int main() {
    int size;
    cout << "Enter hash table size: ";
    cin >> size;
    cin.ignore();

    HashTable table(size);

    int choice;
    do {
        cout << "\nMenu:\n1. Insert\n2. Delete\n3. Search\n4. Display\n5. Load from file\n6. Update\n7. Exit\nEnter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                EmployeeHashNode Node;
                int key;
                do
                {
                    cout << "Enter key: ";
                    cin >> key;
                } while (key<1000||key>9999);
                cin.ignore();
                Node.Input(key);
                insert(table, Node);
                break;
            }
            case 2: {
                int key;
                cout << "Enter key to delete: ";
                cin >> key;
                Delete(table, key);
                break;
            }
            case 3: {
                int key;
                cout << "Enter key to search: ";
                cin >> key;
                Search(table, key);
                break;
            }
            case 4:
                Display(table);
                break;
            case 5:
                LoadFromFile(table, "EMP.dat");
                break;
            case 6: {
                int key;
                cout << "Enter key to update: ";
                cin >> key;
                Update(table, key);
                break;
            }
            case 7:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}