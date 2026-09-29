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


pair<vector<int>, int>
simulatedAnnealing(vector<int> current,
                   mt19937& rng) {

    double T = 100.0;
    double alpha = 0.95;
    double Tmin = 0.1;

    int iterations = 0;

    vector<int> bestRoute = current;

    double currentCost = routeCost(current);
    double bestCost = currentCost;


    uniform_int_distribution<int> index(0, N - 1);
    uniform_real_distribution<double> real01(0.0, 1.0);


    while (T > Tmin) {

        
        int i = index(rng);
        int j = index(rng);

        while (i == j) {
            j = index(rng);
        }


        vector<int> neighbour = current;

        swap(neighbour[i], neighbour[j]);


        double newCost = routeCost(neighbour);

        double deltaE = newCost - currentCost;

        bool accept = false;


        
        if (deltaE < 0) {

            accept = true;
        }

        
        else {

            double probability =
                exp(-deltaE / T);

            double r = real01(rng);

            if (r < probability)
                accept = true;
        }


        if (accept) {

            current = neighbour;
            currentCost = newCost;

            if (currentCost < bestCost) {

                bestCost = currentCost;
                bestRoute = current;
            }
        }


        iterations++;

        cout << "\nIteration: "
             << iterations;

        cout << "\nTemperature: "
             << T;

        cout << "\nCurrent Cost: "
             << currentCost;

        cout << "\nBest Cost: "
             << bestCost;

        cout << "\nMove: "
             << (accept ? "Accepted" : "Rejected")
             << endl;


        
        T *= alpha;
    }


    return {bestRoute, iterations};
}


int main() {

    random_device rd;
    mt19937 rng(rd());

    vector<int> route =
        {0,1,2,3,4,5,6};

    shuffle(route.begin(), route.end(), rng);

    cout << "Initial Route: ";
    printRoute(route);

    cout << "\nInitial Cost = "
         << routeCost(route)
         << endl;


    auto [bestRoute, iterations] =
        simulatedAnnealing(route, rng);


    cout << "\nFinal Best Route: ";
    printRoute(bestRoute);

    cout << "\nFinal Best Cost = "
         << routeCost(bestRoute)
         << endl;

    cout << "Iterations = "
         << iterations
         << endl;

    return 0;
}
