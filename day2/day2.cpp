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


int main()
{

    // puzzle variables
    string str;
    vector<int> v;
    int res = 0;


    // open puzzle input
    ifstream f("input.csv");
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
        vector<int> pos, len;

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
        int i = 1;
        int tmp_res = 1;
        while ( tmp_res!=0 && i < v.size()-1 )
        {
            tmp_res *= inRange(1, 3, abs(v[i]-v[i-1]));
            tmp_res *= inRange(1, 3, abs(v[i+1]-v[i]));
            tmp_res *= ( sign(v[i]-v[i-1])==sign(v[i+1]-v[i]) );
            if (debug) debug_file << "current val: " << v[i] << endl;
            if (debug) debug_file << "---" << endl;
            i++;
        }
        res += tmp_res;
        if (debug) debug_file << "tmp_res : " << tmp_res << endl;
        if (debug) debug_file << "---" << endl;
    }
    cout << "res part. 1 : " << res << endl;
    f.close();
    debug_file.close();

    return 0;
}