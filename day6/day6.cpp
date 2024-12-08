#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

enum corner { UL, UR, DR, DL };

using namespace std;

int lookForNextObstacle(const vector<int> &obstacles, int i, int j, const int d[2], const int height, const int width)
{

    // print values
    // cout << "i: " << i << endl;
    // cout << "j: " << j << endl;
    // cout << "width: " << width << endl;
    // cout << "height: " << height << endl;
    // cout << "d: " << d[0] << ", " << d[1] << endl;

    // look on row or column ?
    int k = i*abs(d[0]) + j*abs(d[1]);
    int criteria = height*abs(d[0]) + width*abs(d[1]);
    int p = -1;

    while ( k >= 0 && k < criteria)
    {
        if (d[0] != 0)  p = k*width + j;
        else            p = i*width + k;
        // cout << "p: " << p << endl;

        auto it = find(obstacles.begin(), obstacles.end(), p);
        if (it != obstacles.end())
        {
            cout << "found next obstacles in position " << p << endl;
            return p;
        }
        k+=(d[0]+d[1]);
    }
    return -1;
}

void printCorner(const corner &c)
{
    switch(c)
    {
        case UL: cout << "UL" << endl; break;
        case UR: cout << "UR" << endl; break;
        case DR: cout << "DR" << endl; break;
        case DL: cout << "DL" << endl; break;
    }
}

void cornerRotation(corner &c)
{
    switch(c)
    {
        case UL: c = UR;    break;
        case UR: c = DR;    break;
        case DR: c = DL;    break;
        case DL: c = UL;    break;
    }
}

int computeMissingCorner(const int p1, const int p3, const corner c, const int width)
{
    int p4;
    switch(c)
    {
        // p = i*width+j
        case UL: p4 = ((p1/width)-1)*width + ((p3%width)+1);    break;
        case UR: p4 = ((p3/width)+1)*width + ((p1%width)+1);    break;
        case DR: p4 = ((p1/width)+1)*width + ((p3%width)-1);    break;
        case DL: p4 = ((p3/width)-1)*width + ((p1%width)-1);    break;
    }
    return p4;
}

bool isNextCornerBeformeMissingOne(const int added_obstacle, const int existing_obstacle, const corner c, const int width)
{
    bool res;

    int i_a = (added_obstacle / width);
    int j_a = (added_obstacle % width);

    int i_e = (existing_obstacle / width);
    int j_e = (existing_obstacle % width);

    switch(c)
    {
        // p = i*width+j
        case UL: res = (i_a < i_e);     break;
        case UR: res = (j_a > j_e);     break;
        case DR: res = (i_a > i_e);     break;
        case DL: res = (j_a < j_e);     break;
    }
    return res;
}


int lookForNextCorner(const vector<int> &obstacles, const corner c, const int pos, const int width, const int height)
{
    int i = (pos / width);
    int j = (pos % width);
    int d[2];

    switch(c)
    {
        case UL  : i+=1; d[0]=0; d[1]=1;    break;
        case UR  : j-=1; d[0]=1; d[1]=0;    break;
        case DR  : i-=1; d[0]=0; d[1]=-1;   break;
        case DL  : j+=1; d[0]=-1; d[1]=0;   break;
    }
    printCorner(c);
    return lookForNextObstacle(obstacles, i, j, d, height, width);
}


int main()
{
    // puzzle variables
    string str;
    vector<int> obstacles, visited_positions, added_obstacles;
    int guard_pos[2];
    int width, height;
    int res = 0;

    // open puzzle input
    ifstream f("test_input.txt");
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

    
    // Part. 1:  guard's route
    res = 0;
    int d[2] = {-1, 0};     // direction of the guard expressed in the table frame, rows then columns
    int curr_pos, next_pos;

    while ( (guard_pos[0] >= 0) && (guard_pos[0] <= height-1) 
            && (guard_pos[1] >= 0) && (guard_pos[1] <= width-1)
            )
    {
        // cout << "guard_pos: " << guard_pos[0] << ", " << guard_pos[1] << endl;

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


    // Part. 2: put the guard in a loop
    res = 0;
    for (int pos : obstacles)
    {   
        // position in row-column
        int i = (pos / width);
        int j = (pos % width);
        cout << "---" << endl;
        cout << "obstacle in (" << i << ", " << j << ")" << endl;

        vector<corner> corners = { UL, UR, DR, DL };
        for (corner c : corners)
        {
            cout << "starting research from corner ";
            printCorner(c);
            cout << endl;

            bool solution = true;
            int added_obs = -1;
            int c_pos = pos;
            int n = 0;

            // look for two corners from the current one
            do
            {
                c_pos = lookForNextCorner(obstacles, c, c_pos, width, height);
                cornerRotation(c);
                n++;
            }
            while ( c_pos!=-1 && n<2 );

            if (c_pos!=-1)  // do nothing if a corner has not been found
            {
                // compute the position of the missing corner
                added_obs = computeMissingCorner(pos, c_pos, c, width);

                // check if the missing corner can be achieved from the current corner (if not other obstacle is on the way)
                auto next_obstacle = lookForNextCorner(obstacles, c, c_pos, width, height);
                if (next_obstacle!=-1 && !isNextCornerBeformeMissingOne(added_obs, next_obstacle, c, width)) 
                    solution=true;
                else 
                {
                    cout << "An obstacle is on the way." << endl;
                    solution = false;
                }

                // check if the added obstacle does not already exists in the added obstacles
                if (find(added_obstacles.begin(), added_obstacles.end(), added_obs) == added_obstacles.end())
                    solution = true;
                else 
                {
                    cout << "The obstacle has alredy been added to the list of the possible ones." << endl;
                    solution = false;
                }

                // check if the added obstacle does not already exists as an obstacle
                if (find(obstacles.begin(), obstacles.end(), added_obs) == obstacles.end())
                    solution = true;
                else 
                {
                    cout << "The obstacle already exists." << endl;
                    solution = false;
                }

                // add the obstacle
                if (solution)
                {
                    res++;
                    added_obstacles.push_back(added_obs);
                    cout << "added obstacle: " << added_obs << endl; 
                }
            } // if (c_pos!=-1)
        }
        








    /*

        // look from up-left corner
        if (!solution)
        {
            cout << "search from up-left corner" << endl;
            // look for up-right corner
            i = i+1; d[0]=0; d[1]=1;
            auto p = lookForNextObstacle(obstacles, i, j, d, height, width);
            
            // look for down-right corner
            if ( p!=-1 )
            {
                j = (p % width)-1; d[0]=1; d[1]=0;
                auto p = lookForNextObstacle(obstacles, i, j, d, height, width);

                // found a solution
                if ( p!=-1 )
                {
                    // I also should check if there is no obstacle before

                    // position of the added obstacle in the down-left corner
                    // check if it has not been found before
                    i = (p / width)-1; j = (pos % width)-1;
                    added_obs = i*width + j;
                    if (find(added_obstacles.begin(), added_obstacles.end(), added_obs) == added_obstacles.end()
                        && find(obstacles.begin(), obstacles.end(), added_obs) == obstacles.end()
                        ) 
                    {
                        res++;
                        solution=true;
                        added_obstacles.push_back(added_obs);
                        cout << "added obstacle: " << added_obs << endl;
                    }
                }
            }
        }

        // look from up-right corner
        if (!solution)
        {
            cout << "search from up-right corner" << endl;
            int i = (pos / width);
            int j = (pos % width);

            // look for down-right corner
            j = j-1; d[0]=1; d[1]=0;
            auto p = lookForNextObstacle(obstacles, i, j, d, height, width);
            
            // look for down-left corner
            if ( p!=-1 )
            {
                i = (p / width)-1; d[0]=0; d[1]=-1;
                auto p = lookForNextObstacle(obstacles, i, j, d, height, width);

                // found a solution
                if ( p!=-1 )
                {
                    // position of the added obstacle in the up-left corner
                    // check if it has not been found before
                    i = (pos / width)-1; j = (p % width)+1;
                    added_obs = i*width + j;
                    if (find(added_obstacles.begin(), added_obstacles.end(), added_obs) == added_obstacles.end()
                        && find(obstacles.begin(), obstacles.end(), added_obs) == obstacles.end()
                        ) 
                    {
                        res++;
                        solution=true;
                        added_obstacles.push_back(added_obs);
                        cout << "added obstacle: " << added_obs << endl;
                    }
                }
            }
        }

        // look from down-right corner
        if (!solution)
        {
            cout << "search from down-right corner" << endl;
            int i = (pos / width);
            int j = (pos % width);

            // look for down-left corner
            i = i-1; d[0]=0; d[1]=-1;
            auto p = lookForNextObstacle(obstacles, i, j, d, height, width);
            
            // look for down-left corner
            if ( p!=-1 )
            {
                j = (p % width)+1; d[0]=-1; d[1]=0;
                auto p = lookForNextObstacle(obstacles, i, j, d, height, width);

                // found a solution
                if ( p!=-1 )
                {
                    // position of the added obstacle in the up-right corner
                    // check if it has not been found before
                    i = (p / width)+1; j = (pos % width)+1;
                    added_obs = i*width + j;
                    if (find(added_obstacles.begin(), added_obstacles.end(), added_obs) == added_obstacles.end()
                        && find(obstacles.begin(), obstacles.end(), added_obs) == obstacles.end()
                        ) 
                    {
                        res++;
                        solution=true;
                        added_obstacles.push_back(added_obs);
                        cout << "added obstacle: " << added_obs << endl;
                    }
                }
            }
        }

        // look from down-left corner
        if (!solution)
        {
            cout << "search from down-left corner" << endl;
            int i = (pos / width);
            int j = (pos % width);

            // look for up-left corner
            j = j+1; d[0]=-1; d[1]=0;
            auto p = lookForNextObstacle(obstacles, i, j, d, height, width);
            
            // look for down-left corner
            if ( p!=-1 )
            {
                i = (p / width)+1; d[0]=0; d[1]=1;
                auto p = lookForNextObstacle(obstacles, i, j, d, height, width);

                // found a solution
                if ( p!=-1 )
                {
                    // position of the added obstacle in the down-right corner
                    // check if it has not been found before
                    i = (pos / width)+1; j = (p % width)-1;
                    added_obs = i*width + j;
                    if (find(added_obstacles.begin(), added_obstacles.end(), added_obs) == added_obstacles.end()
                        && find(obstacles.begin(), obstacles.end(), added_obs) == obstacles.end()
                        ) 
                    {
                        res++;
                        solution=true;
                        added_obstacles.push_back(added_obs);
                        cout << "added obstacle: " << added_obs << endl;
                    }
                }
            }
        }

    */

    }

    cout << "res: " << res << endl;
    return 0;
}