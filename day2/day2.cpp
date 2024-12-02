#include <iostream>
#include <fstream>
#include <stdlib.h>     /* abs */
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;


bool inRange(int low, int high, int x)          
{   
    bool res = (low <= x && x <= high);
    // cout << "low : " << low;
    // cout << "; high : " << high;
    // cout << "; x : " << x;
    // cout << "; res : " << res;
    // cout << endl;
    return res;  
}

int customSign(int val)
{
    int res = (val>=0) ? 1 : -1;
    // cout << "val : " << val << "; res : " << res << endl;
    return res;
}


int main()
{

    // puzzle variables
    string str;
    vector<int> v;
    int res = 0;


    // open puzzle input
    ifstream f("input.csv");
    if (!f.is_open())
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

        // for (int i=0; i < pos.size(); i++)
        // {
        //     cout << "pos: " << pos[i] << "; len: " << len[i] << endl;
        // }


        // fill vector of the line
        v.clear();
        // cout << "v : ";
        for (int i=0; i < pos.size(); i++)
        {
            v.push_back(stoi(str.substr(pos[i],len[i])));
            // cout << "\"" << v.back() << "\", ";
        }
        // cout << endl;


        // compute result
        int i = 1;
        int tmp_res = 1;
        while ( tmp_res!=0 && i < v.size()-1 )
        {
            tmp_res *= inRange(1, 3, abs(v[i]-v[i-1]));
            tmp_res *= ( customSign(v[i]-v[i-1])==customSign(v[i+1]-v[i]) );
            // cout << "current val: " << v[i] << endl;
            // cout << "---" << endl;
            i++;
        }
        res += tmp_res;  
    }
    cout << "res part. 1 : " << res << endl;
    f.close();

    return 0;
}