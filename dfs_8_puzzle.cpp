#include <bits/stdc++.h>
using namespace std;

using State = vector<int>;

const State GOAL = {
    1,2,3,
    4,5,6,
    7,8,0
};


void printBoard(const State& state) {

    for (int i = 0; i < 9; i++) {

        if (state[i] == 0)
            cout << "_ ";
        else
            cout << state[i] << " ";

        if (i % 3 == 2)
            cout << '\n';
    }

    cout << '\n';
}


string stateToString(const State& state) {

    string s;

    for (int x : state)
        s += char('0' + x);

    return s;
}


vector<State> getNeighbors(const State& state) {

    vector<State> result;

    int zero =
        find(
            state.begin(),
            state.end(),
            0
        ) - state.begin();


    int row = zero / 3;
    int col = zero % 3;


    if (row > 0) {

        State next = state;

        swap(next[zero],
             next[zero - 3]);

        result.push_back(next);
    }


    if (row < 2) {

        State next = state;

        swap(next[zero],
             next[zero + 3]);

        result.push_back(next);
    }


    if (col > 0) {

        State next = state;

        swap(next[zero],
             next[zero - 1]);

        result.push_back(next);
    }


    if (col < 2) {

        State next = state;

        swap(next[zero],
             next[zero + 1]);

        result.push_back(next);
    }


    return result;
}


void printPath(
    map<string, State>& states,
    map<string, string>& parent,
    string goalKey) {

    vector<State> path;

    string current = goalKey;


    while (current != "") {

        path.push_back(
            states[current]
        );

        current =
            parent[current];
    }


    reverse(
        path.begin(),
        path.end()
    );


    cout << "\nSolution Path:\n";

    for (int i = 0;
         i < path.size();
         i++) {

        cout << "Move "
             << i
             << ":\n";

        printBoard(path[i]);
    }


    cout << "Number of moves = "
         << path.size() - 1
         << endl;
}


bool DFS(State start) {

    stack<State> st;

    map<string, bool> visited;

    map<string, State> states;

    map<string, string> parent;


    string startKey =
        stateToString(start);


    st.push(start);

    visited[startKey] = true;

    states[startKey] = start;

    parent[startKey] = "";


    while (!st.empty()) {

        State current = st.top();

        st.pop();


        string currentKey =
            stateToString(current);


        if (current == GOAL) {

            printPath(
                states,
                parent,
                currentKey
            );

            return true;
        }


        vector<State> neighbours =
            getNeighbors(current);


        
        
        
        reverse(
            neighbours.begin(),
            neighbours.end()
        );


        for (State next : neighbours) {

            string nextKey =
                stateToString(next);


            if (!visited[nextKey]) {

                visited[nextKey] = true;

                states[nextKey] = next;

                parent[nextKey] =
                    currentKey;

                st.push(next);
            }
        }
    }


    return false;
}


int main() {

    State start = {
        1,2,3,
        4,0,6,
        7,5,8
    };


    cout << "Initial State:\n";

    printBoard(start);


    if (!DFS(start))
        cout << "No solution found.\n";


    return 0;
}
