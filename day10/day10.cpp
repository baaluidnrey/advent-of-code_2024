#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <unordered_map>

#define debug false

using namespace std;

int lookNextStep(const vector<int> &map, vector<int> &summits, unordered_map<int, int> &path, int &pos, const int &width, const int &height)
{
    int i = pos / width;
    int j = pos % width;
    path[pos] = map[pos];

    for (int di=-1; di<=1; di++)
    {
        for (int dj=-1; dj<=1; dj++)
        {
            if ( (i+di)>=0 && (i+di)<height && (j+dj)>=0 && (j+dj)<width 
                  && abs(di)!=abs(dj)
                  )
            {
                int next_p = (i+di)*width + (j+dj);

                if (map[next_p]==map[pos]+1) 
                {
                    if (map[next_p]==9) // && find(summits.begin(), summits.end(), next_p)==summits.end())
                    {
                        path[next_p] = map[next_p];
                        summits.push_back(next_p); // add it if it does not already exists for part. 1 | always for part. 2
                    }
                    else lookNextStep(map, summits, path, next_p, width, height);
                }
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
    unordered_map<int, int> path;
    unordered_map<int, vector<int>> trailheads;
    int width, height;
    int res = 0;


    // open puzzle input
    ifstream f("input.txt");
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
    if (debug)
    {
        cout << "map" << endl;
        for (int i=0; i<height; i++)
        {
            for (int j = 0; j<width; j++)
                cout << " " << map[i*width+j] << " ";
            cout << endl;
        }
    }


    // search for paths in map

    for (int p = 0; p<map.size(); p++)
    {
        if (map[p]==0)
        {
            // initialization of path
            for (int i = 0; i<map.size(); i++) path[i] = -1;

            summits.clear();
            lookNextStep(map, summits, path, p, width, height);

            // copy summits in tmp summits
            tmp_summits.clear();
            tmp_summits.insert(tmp_summits.begin(), summits.begin(), summits.end());
            trailheads[p] = tmp_summits;

            // display map
            if (debug)
            {
                cout << "--- " << (int) p/width << ", " << (int) p%width << " ---" << endl;
                cout << tmp_summits.size() << " summits" << endl;
                for (int i=0; i<height; i++)
                {
                    for (int j = 0; j<width; j++)
                    {

                        int val = path[i*width+j];
                        if (val==-1)    cout << "   ";
                        else            cout << " " << path[i*width+j] << " ";
                    }
                    cout << endl;
                }
            }
        }
    }

    // display trailheads and compute res
    res = 0;
    for (auto it : trailheads)
    {
        res += it.second.size();
        if (debug)
        {
            cout << it.first << ": ";
            for (int i : it.second) cout << "(" << (int) i/width << ", " << (int) i%width << "), ";
            cout << endl;
        }
    }

    cout << "res: " << res << endl;
 
    return 0;
}