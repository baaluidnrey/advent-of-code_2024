#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define debug true

using namespace std;

int main()
{

    // puzzle variables
    string str;
    string regex = "mul(*,*)";
    int res = 0;


    // open puzzle input
    ifstream f("test_input.txt");
    ofstream debug_file;
    debug_file.open("debug_file.txt");
    if (!f.is_open() || !debug_file.is_open())
    {
        cerr << "Error opening the file!";
        return 1;
    }


    // read char by char
    int index = 0;
    char c;
    while (f >> c)
    {
        if (c==regex[index]) index++;
        else if (regex[index]=="*")
        {
            
        }
        else    
    } 

    return 0;
}