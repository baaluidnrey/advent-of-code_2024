#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>

#define debug false

using namespace std;

int main()
{

    // puzzle variables
    string regex = "mul(*,*)";
    string str;
    vector<int> v;
    int res = 0;


    // open puzzle input
    ifstream f("input.txt");
    ofstream debug_file;
    debug_file.open("debug_file.txt");
    if (!f.is_open() || !debug_file.is_open())
    {
        cerr << "Error opening the file!";
        return 1;
    }

    while (getline(f, str))
    {
        regex word_regex("\\d+");
    }


    


/* SELF_IMPLEMENTATION oF REGEX, DOES NOT WORK

    // read char by char
    int index_regex = 0;
    vector<string> v_n;
    string n;
    char c;
    bool look_at_number = false;

    while (f >> c)
    {
        // starting of a new regex ? because first char is unique in the string
        if (c == regex[0])      
        {
            v_n.clear();                                // remove temporary values from v_n
            index_regex=1;                              // re-initialize indexes

            if (debug) cout << "new regex" << endl;
            if (debug) cout << c << " == " << regex[0] << endl;
        }

        // we were looking for number and it's no more one
        else if (look_at_number == true && isdigit(c)==0)
        {
            if (debug) cout << "n: " << n << endl;
            v_n.push_back(n);                       // push in the temporary vector that stores values
            n = "";
            look_at_number = false;
            index_regex++;
        }

        // looking for everything else of numbers
        if (c != '*' && c == regex[index_regex]) 
        {   
            if (debug) cout << c << " == " << regex[index_regex] << endl;
            // we've got the full regex
            if (index_regex==regex.length()-1)
            {
                if (debug)
                {
                    cout << "got a full regex" << endl;
                    for (string n : v_n) cout << n << " ";
                    cout << endl;
                }

                for (string n : v_n) v.push_back(stoi(n));  // put the number in the vector that stores all of them
                v_n.clear();                                // remove temporary values from v_n
                index_regex=0;                              // re-initialize indexes
            }

            else index_regex++;
        }

        else if (regex[index_regex]=='*' and isdigit(c)!=0)
        {
            if (debug) cout << c << endl;
            n.push_back(c);
            look_at_number = true;
        }
    }

    f.close();


    // print vector of numbers
    for (int number : v) cout << number << " ";
    cout << endl;

    // compute result of part. 1
    res = 0;
    for (int i = 0; i < v.size()/2; i++)
    {
        if (v[2*i]<1000 && v[2*i+1]<1000)
            res += v[2*i]*v[2*i+1];
    }
    cout << "res = " << res << endl;

*/

    return 0;
}