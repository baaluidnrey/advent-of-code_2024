#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

#define debug true

using namespace std;

int main()
{
    // puzzle variables
    string str;
    int pos_start, pos_end;
    long test_value;
    long value, tmp_value;
    vector<long> numbers;
    long res = 0;

    // open puzzle input
    ifstream f("input.txt");
    if (!f.is_open())
    {
        cerr << "Error opening the file!";
        return 1;
    }

    while (getline(f, str))
    {
        // extract the test_value
        pos_end = str.find(":");
        test_value = stol(str.substr(0, pos_end));

        // extract the numbers
        numbers.clear();
        pos_start = pos_end+2; pos_end = str.length()-1;

        do 
        {
            pos_end = str.find(" ", pos_start);
            if ( pos_end!=string::npos )
            {
                numbers.push_back(stol(str.substr(pos_start, pos_end)));
                pos_start = pos_end+1;
            }
        }
        while ( pos_end!=string::npos );

        if (pos_start > 0)  numbers.push_back(stol(str.substr(pos_start)));

        // print to check
        if (debug)
        {
            cout << "---" << endl;
            cout << test_value << ": ";
            for (int i : numbers) cout << i << ", ";
            cout << endl;
        }

        // search if a combination of 'x' and '+' can make the equation match the test_value
        for (int i=0; i<pow(2,numbers.size()-1); i++)
        {
            value = numbers[0];
            if (debug)  cout << numbers[0];

            for (int j=1; j<numbers.size(); j++)
            {
                // i = 0x1 means x , i = 0x0 means +

                if ((i>>(j-1))&0x1)     // multiplication
                {
                    value *= numbers[j];
                    if (debug)  cout << 'X';
                }
                
                else                    // addition
                {
                    value += numbers[j];
                    if (debug)  cout << '+';
                }
                if (debug)  cout << numbers[j];
            }
            if (debug)  cout << " = " << value << endl;

            // add the test_value to the result if it is equal to the result of the equation
            if (value == test_value)    
            {
                cout << "add value to res: " << res << endl;
                res+= test_value;
                break;
            }
        }
    }
    
    f.close();

    cout << "res:" << res << endl;

    return 0;
}