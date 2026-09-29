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


char selectMRV() {

    char selected = '?';
    int minimumValues = INT_MAX;

    for (char region : {'A', 'B', 'C', 'D', 'E'}) {

        if (assignment.count(region))
            continue;

        int legalValues = 0;

        for (char color : colors) {

            if (isSafe(region, color))
                legalValues++;
        }

        cout << "Region "
             << region
             << " has "
             << legalValues
             << " remaining values\n";

        if (legalValues < minimumValues) {

            minimumValues = legalValues;
            selected = region;
        }
    }

    return selected;
}


bool backtrackMRV() {

    if (assignment.size() == 5)
        return true;

    char region = selectMRV();

    cout << "\nMRV selected: "
         << region << endl;

    for (char color : colors) {

        cout << "Trying "
             << region << " = "
             << color << endl;

        if (isSafe(region, color)) {

            assignment[region] = color;

            if (backtrackMRV())
                return true;

            cout << "Backtracking from "
                 << region << " = "
                 << color << endl;

            assignment.erase(region);
        }
        else {
            cout << "Rejected\n";
        }
    }

    return false;
}


int main() {

    if (backtrackMRV()) {

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
