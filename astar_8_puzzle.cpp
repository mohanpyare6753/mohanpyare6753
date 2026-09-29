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



int manhattanDistance(
    const State& state) {

    int distance = 0;


    for (int i = 0; i < 9; i++) {

        int tile = state[i];


        if (tile == 0)
            continue;


        
        int goalIndex = tile - 1;


        int currentRow = i / 3;
        int currentCol = i % 3;


        int goalRow =
            goalIndex / 3;

        int goalCol =
            goalIndex % 3;


        distance +=
            abs(currentRow - goalRow)
            +
            abs(currentCol - goalCol);
    }


    return distance;
}


struct Node {

    State state;

    int g;
    int h;
    int f;
};


struct Compare {

    bool operator()(
        const Node& a,
        const Node& b) const {

        return a.f > b.f;
    }
};


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


    cout << "\nA* Solution Path:\n";

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


bool AStar(State start) {

    priority_queue<
        Node,
        vector<Node>,
        Compare
    > pq;


    map<string, int> bestG;

    map<string, State> states;

    map<string, string> parent;


    string startKey =
        stateToString(start);


    int startH =
        manhattanDistance(start);


    pq.push({
        start,
        0,
        startH,
        startH
    });


    bestG[startKey] = 0;

    states[startKey] = start;

    parent[startKey] = "";


    while (!pq.empty()) {

        Node current =
            pq.top();

        pq.pop();


        string currentKey =
            stateToString(
                current.state
            );


        
        if (current.g >
            bestG[currentKey]) {

            continue;
        }


        if (current.state == GOAL) {

            printPath(
                states,
                parent,
                currentKey
            );

            return true;
        }


        for (State next :
             getNeighbors(
                 current.state)) {

            string nextKey =
                stateToString(next);


            int newG =
                current.g + 1;


            if (!bestG.count(nextKey) ||
                newG < bestG[nextKey]) {

                int h =
                    manhattanDistance(next);

                int f = newG + h;


                bestG[nextKey] =
                    newG;

                states[nextKey] =
                    next;

                parent[nextKey] =
                    currentKey;


                pq.push({
                    next,
                    newG,
                    h,
                    f
                });
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


    if (!AStar(start))
        cout << "No solution found.\n";


    return 0;
}
