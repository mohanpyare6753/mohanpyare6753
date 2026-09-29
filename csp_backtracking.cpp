#include <bits/stdc++.h>
using namespace std;

vector<char> colors = {'R', 'G', 'B'};

map<char, vector<char>> neighbors = {
    {'A', {'B', 'C'}},
    {'B', {'A', 'C', 'D', 'E'}},
    {'C', {'A', 'B', 'E'}},
    {'D', {'B', 'E'}},
    {'E', {'B', 'C', 'D'}}
};

map<char, char> assignment;


bool isSafe(char region, char color) {

    for (char neighbour : neighbors[region]) {

        if (assignment.count(neighbour) &&
            assignment[neighbour] == color) {

            return false;
        }
    }

    return true;
}


bool backtrack(vector<char>& variables, int index) {

    if (index == variables.size())
        return true;

    char region = variables[index];

    cout << "\nSelecting region: "
         << region << endl;

    for (char color : colors) {

        cout << "Trying "
             << region << " = "
             << color << endl;

        if (isSafe(region, color)) {

            assignment[region] = color;

            cout << "Accepted\n";

            if (backtrack(variables, index + 1))
                return true;

            cout << "Backtracking from "
                 << region << " = "
                 << color << endl;

            assignment.erase(region);
        }
        else {
            cout << "Rejected: conflict\n";
        }
    }

    return false;
}


int main() {

    vector<char> variables =
        {'A', 'B', 'C', 'D', 'E'};

    if (backtrack(variables, 0)) {

        cout << "\nFinal Assignment:\n";

        for (auto [region, color] : assignment)
            cout << region
                 << " = "
                 << color
                 << endl;
    }
    else {
        cout << "No solution exists.\n";
    }

    return 0;
}
