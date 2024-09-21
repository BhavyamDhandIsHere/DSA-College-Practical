#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <ctime>
#include <bitset>
using namespace std;

void LogFile(const string& event) {
    ofstream BinFile("Machine_Code_Queue.txt",ios_base::app);
    if (BinFile.is_open())
    {
        for (char c:event)
        {
            BinFile<<bitset<8>(c)<<" ";
        }
        BinFile<<endl;
        BinFile.close();
    }
    
}