#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    // puzzle variables
    string str;
    vector<int> obstacles, visited_positions;
    int guard_pos[2];
    int width, height;
    int res = 0;

    // open puzzle input
    ifstream f("input.txt");
    if (!f.is_open())
    {
        cerr << "Error opening the file!";
        return 1;
    }

    // extract map
    width = 0; height = 0;
    while (getline(f, str))
    {
        // compute size
        if (width==0) width=str.length();
        height++;

        // extract features
        for (int j = 0; j < width; j++)
        {
            if (str[j]=='#')        obstacles.push_back((height-1)*width+j);
            else if (str[j]=='^')
            {
                guard_pos[0] = (height-1);
                guard_pos[1] = j;
            }
        }
    }
    cout << "width: " << width << "; height: " << height << endl;
    f.close();

    
    // guard's route
    int d[2] = {-1, 0};     // direction of the guard expressed in the table frame, rows then columns
    int curr_pos, next_pos;

    while ( (guard_pos[0] >= 0) && (guard_pos[0] <= height-1) 
            && (guard_pos[1] >= 0) && (guard_pos[1] <= width-1)
            )
    {
        cout << "guard_pos: " << guard_pos[0] << ", " << guard_pos[1] << endl;

        curr_pos = guard_pos[0]*width + guard_pos[1];
        next_pos = (guard_pos[0]+d[0])*width + (guard_pos[1]+d[1]);
        
        if (find(obstacles.begin(), obstacles.end(), next_pos) != obstacles.end())
        {
            int d0 = d[0];
            d[0]=d[1];
            d[1]=d0*(-1);
        }

        if (find(visited_positions.begin(), visited_positions.end(), curr_pos) == visited_positions.end())
        {
            res++;
            visited_positions.push_back(curr_pos);
        }

        guard_pos[0]+=d[0];
        guard_pos[1]+=d[1];
    }
    cout << "res: " << res << endl;

    return 0;
}