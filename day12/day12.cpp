#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <cmath>

#define debug true

using namespace std;


void displayMap(const vector<char> &map, const int &height, const int &width)
{
    for (int i=0; i<height; i++)
    {
        for (int j = 0; j<width; j++)
            cout << " " << map[i*width+j] << " ";
        cout << endl;
    }
}


void displayArea(const vector<int> &area, const int &height, const int &width)
{
    for (int i=0; i<height; i++)
    {
        for (int j = 0; j<width; j++)
        {
            if (find(area.begin(), area.end(), i*width+j)!=area.end()) 
                    cout << " X ";
            else    cout << "   ";                                          
        }
        cout << endl;
    }
}


void discoverArea(const vector<char> &map, vector<int> &area, const char &plant, 
                    const int &p, const int &height, const int &width)
{
    int i = p / width;
    int j = p % width;
    area.push_back(p);

    for (int di=-1; di<=1; di++)
    {
        for (int dj=-1; dj<=1; dj++)
        {
            if ( (i+di)>=0 && (i+di)<height && (j+dj)>=0 && (j+dj)<width 
                  && abs(di)!=abs(dj)
                  ) {
                int next_p = (i+di)*width + (j+dj);
                if (map[next_p]==plant) {
                    if (find(area.begin(), area.end(), next_p)==area.end()) {
                        discoverArea(map, area, plant, next_p, height, width);
                    }
                }
            } 
        }
    }
}


int main()
{
    // puzzle variables
    string str;
    vector<char> map;
    vector<int> plant_map;
    vector<int> plant_area;
    set<char> plants;
    int width, height;
    long res = 0;

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

        for (char c : str)  {
            map.push_back(c);
            plants.insert(c);
        }
    }
    cout << "width: " << width << "; height: " << height << endl;
    f.close();

    if (debug) displayMap(map, height, width);

    // number of different plants
    cout << plants.size() << " differents plants: ";
    for (auto plant : plants) cout << plant << ", ";
    cout << endl;

    // find the areas of each plant
    for (auto plant : plants)
    {
        plant_map.clear();
        if (debug) cout << "--- plant " << plant << " ---" << endl;

        for (int p = 0; p<width*height; p++)
        {
            if (map[p]==plant && find(plant_map.begin(), plant_map.end(), p)==plant_map.end())
            {
                plant_area.clear();
                discoverArea(map, plant_area, plant, p, height, width);
                for (auto pos : plant_area) plant_map.push_back(pos);

                if (debug) displayArea(plant_area, height, width);
                if (debug) cout << "area: " << plant_area.size() << endl;
            }
        }
    }


    return 0;
}