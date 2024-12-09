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
    vector<long> v;
    vector<long> b;
    int val_space = -1;
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
        b.clear();
        for (int i = 0; i < v.size(); i++)
        {
            int index = (i/2);

            if (i%2==0)         // file
            {
                for (int j = 0; j < v[i]; j++)
                    b.push_back(index);
            }
            else
            {
                for (int j = 0; j < v[i]; j++)
                    b.push_back(val_space);
            }
        }

        if (debug) 
        {   
            cout << "b: ";
            for (int i : b)
            {
                if (i==val_space) cout << '.';
                else cout << i;
            }
            cout << endl;
        }


        // 3. do the permutations

        // part 1.
        /*
        for (int i = b.size()-1; i>=0; i--)
        {
            if (b[i]!=val_space)
            {
                auto it = find(b.begin(), b.end(), val_space);
                if (it != b.end())
                {
                    int p = it - b.begin();
                    if (debug)  cout << "b: " << b[i] << ", p: " << p << endl;

                    if (p>i) break;
                    b[p] = b[i];
                    b[i] = val_space;
                }
            }

            if (debug) 
            {   
                cout << "b: ";
                for (int i : b) cout << i << ", ";
                cout << endl;
            }
        }
        */

        // part. 2
        int val = 0;
        int i = b.size()-1;
        int j, k, l;
        do
        {
            // current value and position
            val = b[i];
            j = i;
            do {i--;}
            while(b[i]==val); // stops when the value changes, current value between (i+1) and j

            // we then need to find a block of size (j-(i+1))+1 = (j-i)
            k = 0; l = 0;
            while ( k < i+1 && l != (j-i) )
            {
                // compute length of space
                if (b[k] == val_space) l++;
                else l=0;
                k++;
            }

            // a space has been found between (k-1) and (k-l)
            if (l == (j-i))
            {
                for (int index = (k-1); index >= (k-l); index--)    b[index] = val;
                for (int index = i+1; index <=j; index++)           b[index] = val_space;
            }

        if (debug) 
        {   
            cout << "b: ";
            for (int i : b)
            {
                if (i==val_space) cout << '.';
                else cout << i;
            }
            cout << endl;
        }

        } while (i>0);
        

        // 4. compute the checksum
        res = 0;
        for (int i = 0; i < b.size(); i++)
        {
            if (debug) cout << "index: " << i << ", val: " << b[i] << endl;
            if (b[i]!=val_space)
                res += (i*b[i]);
        }

    }
    f.close();

    cout << "res: " << res << endl;

    return 0;
}