#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;


int search_word(const vector<char> &v, const int width, const int height, const int pos[2], const int dec[2], const string word)
{
    int index;
    int res = 1;

    for ( int i = 1; i < word.length(); i++)
    {
        index = (pos[0] + i * dec[0]) * width + (pos[1] + i * dec[1]);

        if ( pos[0] + i * dec[0] < 0 || pos[0] + i * dec[0] > height )
        {
            res = 0;
            // cerr << "out of lines" << endl;
            break;
        }

        else if ( pos[1] + i * dec[1] < 0 || pos[1] + i * dec[1] > width )
        {
            res = 0;
            // cerr << "out of rows" << endl;
            break;
        }

        else if ( v[index]!=word[i] )
        {
            res = 0;
            // cerr << "char is not a match: " << v[index] << " != " << word[i] << endl;
            break;
        }
    }

    if (res == 1) cout << "GOT A MATCH" << endl; 


    /*
    do 
    {
        i++;
        index = (pos[0] + i * dec[0]) * width + (pos[1] + i * dec[1]);

        if ( pos[0] + i * dec[0] < 0 || pos[0] + i * dec[0] > height )
        {
            res = 0;
            cerr << "out of lines" << endl;
            break;
        }

        if ( pos[1] + i * dec[1] < 0 || pos[1] + i * dec[1] > width )
        {
            res = 0;
            cerr << "out of rows" << endl;
            break;
        }
    }
    while ( i<word.length()-1 && v[index]==word[i] );
    */

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
            if (v[index] == word[0])
            {   

                cout << "X is at position (" << pos[0] << ", " << pos[1] << ")" << endl;

                // right
                dec[0] = 0; dec[1] = 1;
                res += search_word(v, width, height, pos, dec, word);

                // left
                dec[0] = 0; dec[1] = -1;
                res += search_word(v, width, height, pos, dec, word);

                // up
                dec[0] = -1; dec[1] = 0;
                res += search_word(v, width, height, pos, dec, word);
            
                // bottom
                dec[0] = 1; dec[1] = 0;
                res += search_word(v, width, height, pos, dec, word);

                // up - right
                dec[0] = -1; dec[1] = 1;
                res += search_word(v, width, height, pos, dec, word);

                // up - left
                dec[0] = -1; dec[1] = -1;
                res += search_word(v, width, height, pos, dec, word);  

                // bottom - right
                dec[0] = 1; dec[1] = 1;
                res += search_word(v, width, height, pos, dec, word);

                // bottom - left
                dec[0] = 1; dec[1] = -1;
                res += search_word(v, width, height, pos, dec, word);  
            }
        }
    }

    cout << "res: " << res << endl;

    return 0;
}