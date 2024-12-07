#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <cmath>

using namespace std;

bool break_rules(vector<int> &pages, unordered_map<int, vector<int>> &rules)
{
    for (int page : pages)
    {
        if (rules.count(page) != 0)     // a rule for the page number exists
        {
            auto p_ref = find(pages.begin(), pages.end(), page);
            for (int i : rules[page])
            {
                auto p = find(pages.begin(), pages.end(), i);
                if (p < p_ref)
                    return true;
            }
        }
    }
    return false;
}



int main()
{
    // puzzle variables
    string str;
    unordered_map<int, vector<int>> rules;
    vector<int> pages;
    int pos_start, pos_end;
    bool get_rules=true;
    bool breaking_rules=false;
    bool reshaped=false;
    int res_1 = 0;
    int res_2 = 0;

    // open puzzle input
    ifstream f("input.txt");
    if (!f.is_open())
    {
        cerr << "Error opening the file!";
        return 1;
    }

    while (getline(f, str))
    {
        if (str=="") get_rules=false;

        // extract the rules
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
            if (pos_start > 0)  pages.push_back(stoi(str.substr(pos_start)));


            // does it follow the rules ?
            bool breaking_rules = break_rules(pages, rules);
            reshaped=false;

            
            // part. 1
            if (!breaking_rules and pages.size()>0) 
                res_1+=pages[floor(pages.size()/2)];


            // part. 2
            int nb_reshaping = 0;
            while ( break_rules(pages, rules) )
            {
                // sort the non-working ordering
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

                                cout << "before: ";
                                for (int toto : pages) cout << toto << ", ";
                                cout << endl;

                                pages.erase(p);
                                pages.insert(p_ref, i);

                                cout << "after: ";
                                for (int toto : pages) cout << toto << ", ";
                                cout << endl;
                            }
                        }
                    }
                }
                nb_reshaping++;

                if (nb_reshaping>10)
                {
                    cerr << "Too many reshapings";
                    break;
                }
                reshaped=true;
            }
            if (reshaped && nb_reshaping<=10 && pages.size()>0)
            {
                res_2+=pages[floor(pages.size()/2)];
                cout << "res: " << res_2 << endl;
            }
        }
    }
    f.close();

    cout << "res part. 1: " << res_1 << endl;
    cout << "res part. 2: " << res_2 << endl;

    return 0;
}