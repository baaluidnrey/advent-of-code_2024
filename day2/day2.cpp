#include <iostream>
#include <fstream>
#include <stdlib.h>     /* abs */
#include <vector>
#include <string>
#include <unordered_map>

#define debug true

using namespace std;


bool inRange(int low, int high, int x)          
{
    return (low <= x && x <= high);
}

int sign(int val)
{    
    return (val>=0) ? 1 : -1;
}

int computeBadLevel(const vector<int> &v, vector<int> &pos)
{
    int bad_level = 0;
    for ( int i = 0; i < v.size(); i++ )
    {
        int tmp_res = 1;

        // all decreasing or ascending
        if (i==0 && v.size()>2)
            tmp_res *= ( sign(v[i+1]-v[i])==sign(v[i+2]-v[i+1]) );
        
        else if (i==v.size() && v.size()>2)
            tmp_res *= ( sign(v[i]-v[i-1])==sign(v[i-1]-v[i-2]) );

        else if (inRange(1,v.size()-1,i))
            tmp_res *= ( sign(v[i]-v[i-1])==sign(v[i+1]-v[i]) );

        // difference in range
        if (i>0)
            tmp_res *= inRange(1, 3, abs(v[i]-v[i-1]));

        if (i<v.size()-1)
            tmp_res *= inRange(1, 3, abs(v[i+1]-v[i]));

        // computation of bad level
        if(tmp_res == 0)
        {
            bad_level++;
            pos.push_back(i);
        }
    }
    return bad_level;
}


int main()
{

    // puzzle variables
    string str;
    vector<int> v, pos, len;
    int bad_level;
    int res = 0;


    // open puzzle input
    ifstream f("test_input.csv");
    ofstream debug_file;
    debug_file.open("debug_file.txt");
    if (!f.is_open() || !debug_file.is_open())
    {
        cerr << "Error opening the file!";
        return 1;
    }


    // read input and put data into the arrays
    while (getline(f, str))
    {  
        pos.clear();    // initialization
        len.clear();    // initialization

        pos.push_back(0);                           // initial position
        for (int i=1; i < str.length(); i++)
        {
            if (isdigit(str[i-1]) != 0 && isdigit(str[i]) == 0)
                len.push_back(i-pos.back());

            else if (isdigit(str[i-1]) == 0 && isdigit(str[i]) != 0)
                pos.push_back(i);
        }
        len.push_back(str.length()-pos.back());       // ending length

        if (pos.size() != len.size())
            cerr << "Error: pos and len have different size." << endl;


        // fill vector of the line
        v.clear();
        if (debug) debug_file << "v : ";
        for (int i=0; i < pos.size(); i++)
        {
            v.push_back(stoi(str.substr(pos[i],len[i])));
            if (debug) debug_file << "\"" << v.back() << "\", ";
        }
        if (debug) debug_file << endl;


        // compute result
        pos.clear();
        bad_level = computeBadLevel(v, pos);
        if (bad_level >= 1) res++;
        else
        {
            // v.erase(v.begin()+i);
        }

        if (debug) 
        {
            debug_file << "bad_level: " << bad_level;
            debug_file << "; pos: ";
            for (int i = 0; i < pos.size(); i++)
                debug_file << pos[i] << ", ";
            debug_file << endl;
        }

    }
    cout << "res part. 1 : " << res << endl;
    f.close();
    debug_file.close();

    return 0;
}