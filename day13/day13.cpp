#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <cmath>

#define debug true

using namespace std;


void extractXY(const string &s, vector<long> &xy)
{
    int pos_X = s.find("X"); int pos_Y = s.find("Y");

    if (debug) cout << s << endl;
    if (debug) cout << "X: " << stol(s.substr(pos_X+2, pos_Y-2));
    if (debug) cout << ", Y: " << stol(s.substr(pos_Y+2));
    if (debug) cout << endl;

    xy.push_back(stol(s.substr(pos_X+2, pos_Y-2)));
    xy.push_back(stol(s.substr(pos_Y+2)));
}


void printMachine(const vector<long> &button_A, const vector<long> &button_B, const vector<long> &prize)
{
    cout << "A: (";
    for (auto val : button_A)   cout << val << ", ";
    cout << "), ";

    cout << "B: (";
    for (auto val : button_B)   cout << val << ", ";
    cout << "), ";

    cout << "Prize: (";
    for (auto val : prize)   cout << val << ", ";
    cout << "), ";

    cout << endl;
}


int main()
{
    // puzzle variables
    string str;
    vector<long> button_A, button_B, prize;
    long res = 0;

    // open puzzle input
    ifstream f("test_input.txt");
    if (!f.is_open()) {
        cerr << "Error opening the file!";
        return 1;
    }

    // extract the stones
    while (getline(f, str)) {
    
        // extract data
        if      (str.find("Button A"))  extractXY(str, button_A);
        else if (str.find("Button B"))  extractXY(str, button_B);
        else if (str.find("Prize"))     extractXY(str, prize);

        else {
            if (debug) printMachine(button_A, button_B, prize);
            button_A.clear(); button_B.clear(); prize.clear();
        }
    }
    f.close();

    return 0;
}