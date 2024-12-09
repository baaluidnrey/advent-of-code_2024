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
    vector<int> v;
    string b = "";
    char c;
    int val;
    int res = 0;

    // open puzzle input
    ifstream f("test_input.txt");
    if (!f.is_open())
    {
        cerr << "Error opening the file!";
        return 1;
    }

    while (getline(f, str))
    {

        // 1. fill the vector
        v.clear();
        for (char c : str) v.push_back(c-'0');  // fill the vector

        if (debug) 
        {   
            cout << "v: ";
            for (int i : v) cout << i;
            cout << endl;
        }

        // 2. represent the blocks
        b = "";
        for (int i = 0; i < v.size(); i++)
        {
            int index = (i/2);
            // c =  static_cast<char>(index);       // int to char, does not work : why ??
            auto s = to_string(index); c = s[0];    // int to char, that is super ugly but that works.

            if (i%2==0)         // file
            {
                for (int j = 0; j < v[i]; j++)
                    b.push_back(c);
            }
            else
            {
                for (int j = 0; j < v[i]; j++)
                    b.push_back('.');
            }
        }

        if (debug) 
        {   
            cout << "b: ";
            for (char c : b) cout << c;
            cout << endl;
        }


        // 3. do the permutations
        for (int i = b.length()-1; i>=0; i--)
        {
            if (b[i]!='.')
            {
                auto p = b.find('.');
                if (debug)  cout << "b: " << b[i] << ", p: " << p << endl;
                if (p != string::npos)
                {
                    if (p>i) break;
                    b[p] = b[i];
                    b[i] = '.';
                }
            }

            if (debug) 
            {   
                cout << "b: ";
                for (char c : b) cout << c;
                cout << endl;
            }
        }


        // 4. compute the checksum
        res = 0;
        for (int i = 0; i < b.length(); i++)
        {
            val = b[i];
            cout << "index: " << i << ", val: " << val << endl;
            res += (i*val);
        }
            // res += i*(b[i]-'0');
            // res += i*stoi(b[i]);

    }
    f.close();

    cout << "res: " << res << endl;

    return 0;
}