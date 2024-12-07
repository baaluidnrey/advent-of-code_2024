#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <cmath>

using namespace std;

int main()
{
    // puzzle variables
    string str;
    unordered_map<int, vector<int>> rules;
    vector<int> pages;
    int pos_start, pos_end;
    bool get_rules=true;
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
        if (str=="") get_rules=false;

        if (get_rules)
        {
            pos_end = str.find("|");

            auto p1 = stoi(str.substr(0, pos_end));
            auto p2 = stoi(str.substr(pos_end+1));

            if (rules.count(p1) == 0)   rules[p1] = {p2};
            else                        rules[p1].push_back(p2);
        }

        else
        {
            // extract the pages ordering
            pages.clear();
            pos_start = 0; pos_end = str.length()-1;
            while ( str.find(",", pos_start) != string::npos )
            {
                pos_end =str.find(",", pos_start);
                pages.push_back(stoi(str.substr(pos_start, pos_end)));
                pos_start = pos_end+1;
            }
            pages.push_back(10);
            cout << str.substr(pos_start, str.length()-1) << endl;
            cout << "length of last value: " << str.substr(pos_start, str.length()-1).length() << endl;
            // pages.push_back(stoi(str.substr(pos_start)));
            for (int i : pages) cout << i << ", ";
            cout << endl; 

            // does it follow the rules ?
            bool breaking_rules = false;
            for (int page : pages)
            {
                if (rules.count(page) != 0)     // a rule for the page number exists
                {
                    cout << "page #" << page << " should be before pages ";
                    for (int i : rules[page]) cout << i << ", ";
                    cout << endl;

                    auto p_ref = find(pages.begin(), pages.end(), page);
                    for (int i : rules[page])
                    {
                        auto p = find(pages.begin(), pages.end(), i);
                        if (p < p_ref)
                        {
                            breaking_rules=true;
                            cout << "breaking rules" << endl;
                            break;
                        }
                        if (breaking_rules) break;
                    }
                }
            if (breaking_rules) break;
            }
            
            // if (!breaking_rules) cout << pages.back() << endl;
            // res+=pages[ceil(pages.size()/2)+1];
        }
    }
    f.close();

    cout << "res: " << res << endl;

    return 0;
}