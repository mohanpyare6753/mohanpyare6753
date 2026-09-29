#include <bits/stdc++.h>
using namespace std;

map<string, vector<int>> domain = {
    {"AI",   {1, 2, 3}},
    {"DBMS", {1, 2, 4}},
    {"OS",   {2, 3, 4}},
    {"CN",   {1, 3, 4}}
};

map<string, vector<string>> neighbors = {
    {"AI",   {"DBMS", "OS"}},
    {"DBMS", {"AI", "CN"}},
    {"OS",   {"AI", "CN"}},
    {"CN",   {"DBMS", "OS"}}
};

map<string, int> assignment;


bool isSafe(string course, int slot) {

    for (string neighbour : neighbors[course]) {

        if (assignment.count(neighbour) &&
            assignment[neighbour] == slot) {

            return false;
        }
    }

    return true;
}


string selectMRV() {

    string selected = "";
    int minimum = INT_MAX;

    for (string course :
         {"AI", "DBMS", "OS", "CN"}) {

        if (assignment.count(course))
            continue;

        int count = 0;

        for (int slot : domain[course]) {

            if (isSafe(course, slot))
                count++;
        }

        cout << course
             << " has "
             << count
             << " remaining values\n";

        if (count < minimum) {

            minimum = count;
            selected = course;
        }
    }

    return selected;
}


bool forwardChecking(string course, int slot) {

    for (string neighbour :
         neighbors[course]) {

        if (assignment.count(neighbour))
            continue;

        vector<int> newDomain;

        for (int value :
             domain[neighbour]) {

            if (value != slot)
                newDomain.push_back(value);
        }

        domain[neighbour] = newDomain;

        if (domain[neighbour].empty()) {

            cout << "Forward Checking: "
                 << neighbour
                 << " has empty domain\n";

            return false;
        }
    }

    return true;
}


bool backtrack() {

    if (assignment.size() == 4)
        return true;

    string course = selectMRV();

    cout << "\nSelected using MRV: "
         << course << endl;

    
    map<string, vector<int>> oldDomain = domain;

    for (int slot : domain[course]) {

        cout << "Trying "
             << course
             << " = Slot "
             << slot << endl;

        if (!isSafe(course, slot)) {

            cout << "Rejected\n";
            continue;
        }

        assignment[course] = slot;

        cout << "Assigned "
             << course
             << " = "
             << slot
             << endl;

        if (forwardChecking(course, slot)) {

            cout << "Forward Checking successful\n";

            if (backtrack())
                return true;
        }

        cout << "Backtracking from "
             << course
             << " = "
             << slot
             << endl;

        assignment.erase(course);

        
        domain = oldDomain;
    }

    return false;
}


int main() {

    cout << "University Course Scheduling\n\n";

    if (backtrack()) {

        cout << "\nFinal Timetable:\n";

        for (auto [course, slot] :
             assignment) {

            cout << course
                 << " -> Slot "
                 << slot
                 << endl;
        }
    }
    else {
        cout << "No valid timetable exists.\n";
    }

    return 0;
}
