#include <bits/stdc++.h>
using namespace std;

const int N = 7;





double x[] = {2, 5, 6, 8, 1, 7, 3};
double y[] = {6, 2, 7, 3, 4, 6, 1};



double distanceBetween(int a, int b) {

    double dx = x[a] - x[b];
    double dy = y[a] - y[b];

    return sqrt(dx * dx + dy * dy);
}



double warehouseDistance(int a) {

    return sqrt(x[a] * x[a] + y[a] * y[a]);
}



double routeCost(const vector<int>& route) {

    double cost = 0.0;

    
    cost += warehouseDistance(route[0]);

    
    for (int i = 0; i < N - 1; i++) {
        cost += distanceBetween(route[i], route[i + 1]);
    }

    
    cost += warehouseDistance(route[N - 1]);

    return cost;
}



void printRoute(const vector<int>& route) {

    cout << "W -> ";

    for (int i : route) {
        cout << char('A' + i) << " -> ";
    }

    cout << "W";
}


pair<vector<int>, int> hillClimbing(vector<int> current) {

    int iterations = 0;

    while (true) {

        double currentCost = routeCost(current);

        vector<int> bestNeighbour = current;
        double bestNeighbourCost = currentCost;


        
        for (int i = 0; i < N; i++) {

            for (int j = i + 1; j < N; j++) {

                vector<int> neighbour = current;

                swap(neighbour[i], neighbour[j]);

                double cost = routeCost(neighbour);

                if (cost < bestNeighbourCost) {

                    bestNeighbourCost = cost;
                    bestNeighbour = neighbour;
                }
            }
        }


        
        if (bestNeighbourCost >= currentCost) {
            break;
        }


        
        current = bestNeighbour;
        iterations++;

        cout << "\nIteration "
             << iterations << ": ";

        printRoute(current);

        cout << "\nCost = "
             << routeCost(current)
             << endl;
    }


    return {current, iterations};
}


int main() {

    random_device rd;
    mt19937 rng(rd());

    vector<int> route = {0,1,2,3,4,5,6};

    
    shuffle(route.begin(), route.end(), rng);

    cout << "Initial Route: ";
    printRoute(route);

    cout << "\nInitial Cost = "
         << routeCost(route)
         << endl;


    auto [bestRoute, iterations] =
        hillClimbing(route);


    cout << "\nFinal Route: ";
    printRoute(bestRoute);

    cout << "\nFinal Cost = "
         << routeCost(bestRoute)
         << endl;

    cout << "Iterations = "
         << iterations
         << endl;

    return 0;
}
