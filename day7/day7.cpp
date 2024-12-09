#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

#define debug false

using namespace std;

int main()
{
    // puzzle variables
    string str;
    int pos_start, pos_end;
    long test_value;
    long value, tmp_value;
    vector<long> numbers, simplified_numbers;
    vector<string> combinations;
    vector<int> combination_index, operations;
    string combination;
    string operators = "+X|";
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
        cout << "---" << endl;
        cout << test_value << ": ";
        for (int i : numbers) cout << i << ", ";
        cout << endl;

        /* PART 1. 

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
        */

        // PART. 2
        
        // create combinations (it would be better to use a tree)
        combination_index.clear();
        for (int i = 0; i<numbers.size()-1; i++)  combination_index.push_back(0);     // initialisation

        int k = 0;
        for (int i = 0; i < pow(operators.length(), numbers.size()-1); i++)
        {

            // print the combination
            if (debug)
            {
                cout << "combination_index: ";
                for (int index : combination_index) cout << index << ", ";
                cout << endl;
            }
            

            // remove the | operations
            
            operations.clear();     // make a copy of combination_index
            operations.insert(operations.begin(), combination_index.begin(), combination_index.end());

            simplified_numbers.clear();     // make a copy of numbers
            simplified_numbers.insert(simplified_numbers.begin(), numbers.begin(), numbers.end());

            // for (int j = 0; j < simplified_numbers.size()-1; j++)
            // {
            //     if (operations[j]==2)   // 2: |
            //     {
            //         int val = stol( to_string(simplified_numbers[j]) + to_string(simplified_numbers[j+1]) );      // quick and dirty, I'm curious bout a way to compute the indice of a number  

            //         simplified_numbers.erase(simplified_numbers.begin()+j);
            //         simplified_numbers[j] = val;
                    
            //         operations.erase(operations.begin()+j);
            //     }
            // }


            // do the + and * computation
            long value = simplified_numbers[0];
            for (int j = 0; j < operations.size(); j++)
            {
                switch(operations[j])   // 0: +, 1: x, 2: |
                {
                    case 0: value+=simplified_numbers[j+1]; break;
                    case 1: value*=simplified_numbers[j+1]; break;
                    case 2: value = stol( to_string(value) + to_string(simplified_numbers[j+1]) ); break;
                }
            }

            // add to the result if the equation equals the value test
            if (value == test_value)
            {
                res+=test_value;
                cout << "add value to res: " << res << endl;
                break;
            }


            // change the combination
            
            combination_index[k]++;
            // if the last index is max, find the index that has to be changed
            if (combination_index[k]==operators.length())
            {
                combination_index[k]=0;
                do {k++;}
                while (k < numbers.size()-2 && combination_index[k]==operators.length()-1); // find the non-max value in ascending direction
                combination_index[k]++;                                                     // increase it
                do {k--; combination_index[k]=0;}                                           // put to zero the others values in descending direction
                while (k > 0);
            }

        }
    
    }
    
    f.close();

    cout << "res:" << res << endl;

    return 0;
}