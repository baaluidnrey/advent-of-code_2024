#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <cmath>

#define debug true

using namespace std;

int main()
{
    // puzzle variables
    string str;
    unordered_map<char, vector<int>> antennas;
    vector<int> antinodes;
    int width = 0;
    int height = 0;
    int res = 0;

    // open puzzle input
    ifstream f("test_input.txt");
    if (!f.is_open())
    {
        cerr << "Error opening the file!";
        return 1;
    }

    // parse the input file
    while (getline(f, str))
    {
        // get size
        if (width==0) width=str.length();
        height++;

        // extract the antennas
        for (int i=0; i<str.length(); i++)
        {
            auto c = str[i];
            if (c!='.') antennas[c].push_back(i + (height-1)*width);    // add the position of the antenna
        }
    }
    f.close();

    // print position of the antennas
    if (debug)
    {
        cout << "antennas:" << endl;
        for (auto it : antennas)
        {
            cout << it.first << ": ";
            for (auto p : it.second) cout << "(" << (int) p/width << "," << (int) p%width << "), ";
            cout << endl; 
        }
    }

    // compute the position of the antinodes
    for (auto it : antennas)
    {
        auto v = it.second; // vector of positions
        for (int i=0; i<v.size(); i++)
        {
            for (int j=i+1; j<v.size(); j++)
            {
                // position of the pair of antennas
                auto p1 = v[i]; int x1 = p1/width; int y1 = p1%width;
                auto p2 = v[j]; int x2 = p2/width; int y2 = p2%width;

                // position of the antinodes
                int dx = x1-x2; int dy = y1-y2;
                // int xa1 = x1 + dx; int ya1 = y1 + dy;
                // int xa2 = x2 - dx; int ya2 = y2 - dy;

                // can we add these positions ?
                int n = 0;
                while ( (x1 + n*dx) >= 0 && (x1 + n*dx) < width && (y1 + n*dx) >= 0 && (y1 + n*dx) < height )
                {
                    int p = (x1 + n*dx)*width + (y1 + n*dx);
                    if ( find(antinodes.begin(), antinodes.end(), p) == antinodes.end() ) antinodes.push_back(p);
                    n++;
                }

                n = 0;
                while ( (x2 - n*dx) >= 0 && (x2 - n*dx) < width && (y2 - n*dx) >= 0 && (y2 - n*dx) < height )
                {
                    int p = (x2 - n*dx)*width + (y2 - n*dx);
                    if ( find(antinodes.begin(), antinodes.end(), p) == antinodes.end() ) antinodes.push_back(p);
                    n++;
                }
            }
        }
    }

    // print position of the antinodes
    if (debug)
    {
        cout << antinodes.size() << " antinodes:" << endl;
        for (auto p : antinodes)
            cout << "(" << (int) p/width << "," << (int) p%width << "), ";
        cout << endl; 
    }

    return 0;
}



