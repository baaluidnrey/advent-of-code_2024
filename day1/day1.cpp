#include <iostream>
#include <fstream>
#include <stdlib.h>     /* abs */
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;


void bubbleSort(vector<int> &v)
{
    int n = v.size();
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (v[j] > v[j + 1])
                swap(v[j], v[j + 1]);
        }

    // print for debugg
    // for (int k=0; k<v.size(); k++)
    //     cout << v[k] << " ";
    // cout << endl;
    }
}


void fill_dict(unordered_map<int, int> &dict, const vector<int> &v)
{
    int n = v.size();
    for (int i = 0; i < n; i++)
    {
        if (dict.count(v[i]) == 0)
            dict[v[i]] = 1;     // initialization
        else
            dict[v[i]] += 1;    // incrementation
    }
}


int main()
{
    // puzzle variables
    string str;
    vector<string> v;
    vector<int> l_list, r_list;
    unordered_map<int, int> l_dict, r_dict;
    int res;

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
        int curr_pos = 0;
        bool number = true;

        pos.push_back(0);   // initial position
        for (int i=0; i < str.length(); i++)
        {
            if (number && isdigit(str[i]) == 0)
            {
                len.push_back(i-curr_pos);
                number = false;
            }

            else if (!number && isdigit(str[i]) != 0)
            {
                curr_pos = i;
                pos.push_back(curr_pos);
                number = true;
            }
        }
        len.push_back(str.length()-curr_pos); // ending length

        // cout << str << endl;
        // cout << "pos: " << pos[0] << " " << pos[1] << endl;
        // cout << "len: " << len[0] << " " << len[1] << endl;

        l_list.push_back(stoi(str.substr(pos[0],len[0])));
        r_list.push_back(stoi(str.substr(pos[1],len[1]))); 
    }
    f.close();

    // sort lists
    bubbleSort(l_list);
    bubbleSort(r_list);


    // compute part. 1 result
    res = 0;
    for (int i = 0; i < l_list.size(); i++)
    {
        res += abs(r_list[i]-l_list[i]);
        
    }
    cout << "part. 1 res = " << res << endl;


    // part. 2
    fill_dict(l_dict, l_list);
    fill_dict(r_dict, r_list);

    // print for debugg
    // for (auto it : l_dict)
    //     cout << it.first << ": " << it.second << endl;
    // for (auto it : r_dict)
    //     cout << it.first << ": " << it.second << endl;

    res = 0;
    for (auto it : l_dict)
    {
        auto val = it.first;
        res += ( val * l_dict[val] * r_dict[val] );
        cout << "part. 2 res = " << res << endl;
    }

    return 0;
}