#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;


int search_word(const vector<char> &v, const int width, const int height, const int pos[2], const int di, const int dj, const string word)
{
    int index;
    int res = 1;

    for ( int i = 1; i < word.length(); i++)
    {
        index = (pos[0] + i * di) * width + (pos[1] + i * dj);

        if (    ( pos[0] + i * di < 0 || pos[0] + i * di >= height )
             || ( pos[1] + i * dj < 0 || pos[1] + i * dj >= width )
             || ( v[index]!=word[i] )
           )
        {
            res = 0;
            break;
        }
    }

    // if (res == 1) cout << "GOT A MATCH" << endl; 

    return res;
}



int main()
{

    // puzzle variables
    string str;
    vector<char> v;
    int width, height;
    int pos[2], dec[2];
    string word="XMAS";
    int index = 0;
    int res = 0;


    // open puzzle input
    ifstream f("test_input.txt");
    if (!f.is_open())
    {
        cerr << "Error opening the file!";
        return 1;
    }

    // fill the vector v
    width = 0;
    height = 0;
    while (getline(f, str))
    {
        // compute size
        if (width==0) width=str.length();
        height++;

        // fill v
        for (char c : str)
            v.push_back(c);
    }
    cout << "width: " << width << "; height: " << height << endl;
    f.close();

    for (char c : v) cout << c;
    cout << endl;


    // look to the word XMAS
    for (int i = 0; i<height; i++)
    {
        for (int j = 0; j<width; j++)
        {
            // compute index in v
            index = i*width + j;
            pos[0] = i; pos[1] = j;

            // search XMAX
            if (v[index] == 'A')
            {
                cout << "A is at position (" << pos[0] << ", " << pos[1] << ")" << endl;

                int n_MAS = 0;

                n_MAS += ( ( search_word(v, width, height, pos, 0, 1, "AS") == 1 && search_word(v, width, height, pos, 0, -1, "AM") == 1 ) );   // right
                n_MAS += ( ( search_word(v, width, height, pos, 0, -1, "AS") == 1 && search_word(v, width, height, pos, 0, 1, "AM") == 1 ) );   // left
                n_MAS += ( ( search_word(v, width, height, pos, -1, 0, "AS") == 1 && search_word(v, width, height, pos, 1, 0, "AM") == 1 ) );   // up
                n_MAS += ( ( search_word(v, width, height, pos, 1, 0, "AS") == 1 && search_word(v, width, height, pos, -1, 0, "AM") == 1 ) );   // down
                n_MAS += ( ( search_word(v, width, height, pos, -1, 1, "AS") == 1 && search_word(v, width, height, pos, 1, -1, "AM") == 1 ) );  // up-right
                n_MAS += ( ( search_word(v, width, height, pos, -1, -1, "AS") == 1 && search_word(v, width, height, pos, 1, 1, "AM") == 1 ) );  // up-left
                n_MAS += ( ( search_word(v, width, height, pos, 1, 1, "AS") == 1 && search_word(v, width, height, pos, -1, -1, "AM") == 1 ) );  // down-right
                n_MAS += ( ( search_word(v, width, height, pos, 1, -1, "AS") == 1 && search_word(v, width, height, pos, -1, 1, "AM") == 1 ) );  // down-left

                if (n_MAS >= 2)
                {
                    cout << "GOT A X-MAX" << endl;
                    res++;
                }
            }
        }
    }

    cout << "res: " << res << endl;

    return 0;
}