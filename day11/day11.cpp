#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <cmath>

#define debug false

using namespace std;

void addStoneToMap(unordered_map<long, long> &stones, long val, long nb) 
{
    if ((stones.count(val) == 0))   stones[val] = nb;
    else                            stones[val] += nb ;
}

void printMap(unordered_map<long, long> &map)
{
    cout << "map: ";
    for (auto it : map) cout << "(" << it.first << ": " << it.second << "), ";
    cout << endl;
}


int main()
{
    // puzzle variables
    string str;
    unordered_map<long, long> stones, stones_tmp;
    int nb_blinks = 75;
    int pos_start, pos_end;
    long res = 0;

    // open puzzle input
    ifstream f("input.txt");
    if (!f.is_open()) {
        cerr << "Error opening the file!";
        return 1;
    }

    // extract the stones
    while (getline(f, str)) {

        stones.clear();
        pos_start = 0; pos_end = str.length()-1;

        do {
            pos_end = str.find(" ", pos_start);
            if ( pos_end!=string::npos ) {
                addStoneToMap(stones, stol(str.substr(pos_start, pos_end)), 1);
                pos_start = pos_end+1;
            }
        } while ( pos_end!=string::npos );

        if (pos_start > 0)  addStoneToMap(stones, stol(str.substr(pos_start)), 1);

        // print to check
        if (debug) printMap(stones);
    }
    f.close();


    // blink and make the transformations of stones
    int i = 0;
    do {
        stones_tmp.clear();

        for (auto it : stones) {

            auto val = it.first;
            auto nb = it.second; 

            // rule #1 : If the stone is engraved with the number 0, it is replaced by a stone engraved with the number 1
            if (val==0)   addStoneToMap(stones_tmp, 1, nb);

            // rule #2 : If the stone is engraved with a number that has an even number of digits, it is replaced by two stones.
            // The left half of the digits are engraved on the new left stone, and the right half of the digits are engraved on the new right stone. 
            // (The new numbers don't keep extra leading zeroes: 1000 would become stones 10 and 0.)
            else if (to_string(val).length()%2 == 0) {
                string s = to_string(val);
                int l = s.length()/2;
                addStoneToMap(stones_tmp, stol(s.substr(0,l)), nb);
                addStoneToMap(stones_tmp, stol(s.substr(l)), nb);
            }

            // rule #3 : If none of the other rules apply, the stone is replaced by a new stone; the old stone's number multiplied by 2024 is engraved on the new stone.
            else    addStoneToMap(stones_tmp, val*2024, nb);
        }

        // put the content of stones_tmp in stones
        stones.clear();
        stones.insert(stones_tmp.begin(), stones_tmp.end());

        // display stones
        if (debug) printMap(stones);

        i++;
        cout << "i: " << i << endl;
    } while (i!=nb_blinks);


    // print the result
    res = 0;
    for (auto it : stones) res += it.second;
    cout << "number of stones after " << nb_blinks << ": " << res << endl;

    return 0;
}