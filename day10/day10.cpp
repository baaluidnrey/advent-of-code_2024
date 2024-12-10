#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <unordered_map>

#define debug false

using namespace std;

int lookNextStep(const vector<int> &map, vector<int> &summits, int &pos, const int &width, const int &height)
{
    if (debug) cout << "pos: " << pos << endl;
    int i = pos / width;
    int j = pos % width;
    if (debug) cout << " - " << map[pos] << ": (" << i << ", " << j << ")" << endl;

    for (int di=-1; di<=1; di++)
    {
        for (int dj=-1; dj<=1; dj++)
        {
            if ( (i+di)>=0 && (i+di)<height && (j+dj)>=0 && (j+dj)<width )
            {
                int next_p = (i+di)*width + (j+dj);

                if (map[next_p]==9)
                {
                    if (debug) cout << "found a summit in position (" << (i+di) << ", " << (j+dj) << ")" << endl;
                    if (find(summits.begin(), summits.end(), next_p)==summits.end()) summits.push_back(next_p); // add it if it does not already exists
                }

                else if (map[next_p]==map[pos]+1) lookNextStep(map, summits, next_p, width, height);

            } 
        }
    }
    return 0;
}


int main()
{

    // puzzle variables
    string str;
    vector<int> map;
    vector<int> summits, tmp_summits;
    unordered_map<int, vector<int>> trailheads;
    int width, height;
    int res = 0;


    // open puzzle input
    ifstream f("test_input.txt");
    if (!f.is_open())
    {
        cerr << "Error opening the file!";
        return 1;
    }

    // fill the map
    width = 0;
    height = 0;
    while (getline(f, str))
    {
        // compute size
        if (width==0) width=str.length();
        height++;

        // fill v
        for (char c : str)
            map.push_back(c-'0');
    }
    cout << "width: " << width << "; height: " << height << endl;
    f.close();

    // display map
    cout << "map" << endl;
    for (int i=0; i<height; i++)
    {
        for (int j = 0; j<width; j++)
            cout << " " << map[i*width+j] << " ";
        cout << endl;
    }


    // search for paths in map
    // for (int p : map)
    for (int p = 0; p<map.size(); p++)
    {
        if (map[p]==0)
        {
            if (debug) cout << "---" << endl;
            summits.clear();
            lookNextStep(map, summits, p, width, height);

            // copy summits in tmp summits
            tmp_summits.clear();
            tmp_summits.insert(tmp_summits.begin(), summits.begin(), summits.end());
            trailheads[p] = tmp_summits;
        }
    }

    // display trailheads and compute res
    res = 0;
    for (auto it : trailheads)
    {
        res += it.second.size();
        cout << it.first << ": ";
        for (int i : it.second) cout << "(" << (int) i/width << ", " << (int) i%width << "), ";
        cout << endl;
    }

    cout << "res: " << res << endl;
 
    return 0;
}