#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

#define debug false

using namespace std;

int main()
{
    // puzzle variables
    string str;
    vector<long> stones;
    int pos_start, pos_end;
    int nb_blinks = 75;
    long res = 0;

    // open puzzle input
    ifstream f("input.txt");
    if (!f.is_open()) {
        cerr << "Error opening the file!";
        return 1;
    }

    while (getline(f, str)) {

        // extract the stones
        stones.clear();
        pos_start = 0; pos_end = str.length()-1;

        do {
            pos_end = str.find(" ", pos_start);
            if ( pos_end!=string::npos )
            {
                stones.push_back(stol(str.substr(pos_start, pos_end)));
                pos_start = pos_end+1;
            }
        } while ( pos_end!=string::npos );

        if (pos_start > 0)  stones.push_back(stol(str.substr(pos_start)));


        // print to check
        for (long i : stones) cout << i << ", ";
        cout << endl;


        // blink and make the transformations of stones
        int i = 0; int j = 0;
        do {
            j = 0;
            do {
                // rule #1 : If the stone is engraved with the number 0, it is replaced by a stone engraved with the number 1
                if (stones[j]==0)   stones[j]=1;

                // rule #2 : If the stone is engraved with a number that has an even number of digits, it is replaced by two stones.
                // The left half of the digits are engraved on the new left stone, and the right half of the digits are engraved on the new right stone. 
                // (The new numbers don't keep extra leading zeroes: 1000 would become stones 10 and 0.)
                else if (to_string(stones[j]).length()%2 == 0) {
                    string s = to_string(stones[j]);
                    int l = s.length()/2;
                    stones[j] = stol(s.substr(0,l));
                    stones.insert(stones.begin()+(j+1), stol(s.substr(l)));
                    j++;
                }

                // rule #3 : If none of the other rules apply, the stone is replaced by a new stone; the old stone's number multiplied by 2024 is engraved on the new stone.
                else    stones[j]*=2024;

                j++;
            } while(j<stones.size());

        // display stones
        if (debug) {
            for (long i : stones) cout << i << ", ";
            cout << endl;
        }

        i++;
        cout << "i: " << i << ", nb_stones: " << stones.size() << endl;
        } while (i!=nb_blinks);


    }
    f.close();

    cout << "number of stones after " << nb_blinks << ": " << stones.size() << endl;

    return 0;
}