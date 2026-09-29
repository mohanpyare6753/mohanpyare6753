#include <bits/stdc++.h>
using namespace std;

const int POP_SIZE = 6;
const int GENERATIONS = 20;
const double MUTATION_RATE = 0.05;

const int CAPACITY = 15;

int weight[] = {7, 2, 1, 9};
int value[]  = {500, 400, 700, 200};


int totalWeight(string chromosome) {

    int weightSum = 0;

    for (int i = 0; i < 4; i++) {

        if (chromosome[i] == '1')
            weightSum += weight[i];
    }

    return weightSum;
}


int totalValue(string chromosome) {

    int valueSum = 0;

    for (int i = 0; i < 4; i++) {

        if (chromosome[i] == '1')
            valueSum += value[i];
    }

    return valueSum;
}


int fitness(string chromosome) {

    int w =
        totalWeight(chromosome);

    if (w > CAPACITY)
        return 0;

    return totalValue(chromosome);
}


string randomChromosome() {

    string chromosome = "";

    for (int i = 0; i < 4; i++) {

        chromosome +=
            (rand() % 2) + '0';
    }

    return chromosome;
}


string rouletteSelection(
    vector<string>& population) {

    int totalFitness = 0;

    for (string chromosome :
         population) {

        totalFitness +=
            fitness(chromosome);
    }


    if (totalFitness == 0)
        return population[
            rand() % population.size()
        ];


    int r =
        rand() % totalFitness;

    int cumulative = 0;


    for (string chromosome :
         population) {

        cumulative +=
            fitness(chromosome);

        if (r < cumulative)
            return chromosome;
    }


    return population.back();
}


pair<string, string> crossover(
    string parent1,
    string parent2) {

    int point =
        1 + rand() % 3;

    string child1 =
        parent1.substr(0, point) +
        parent2.substr(point);

    string child2 =
        parent2.substr(0, point) +
        parent1.substr(point);

    return {child1, child2};
}


void mutation(string& chromosome) {

    for (int i = 0; i < 4; i++) {

        double r =
            (double)rand() / RAND_MAX;

        if (r < MUTATION_RATE) {

            chromosome[i] =
                (chromosome[i] == '0')
                ? '1'
                : '0';
        }
    }
}


int main() {

    srand(time(0));

    vector<string> population;

    for (int i = 0;
         i < POP_SIZE;
         i++) {

        population.push_back(
            randomChromosome()
        );
    }


    string bestChromosome = "";
    int bestFitness = -1;


    for (int generation = 0;
         generation < GENERATIONS;
         generation++) {

        cout << "\nGeneration "
             << generation + 1
             << endl;


        for (string chromosome :
             population) {

            int w =
                totalWeight(chromosome);

            int v =
                totalValue(chromosome);

            int f =
                fitness(chromosome);


            cout << chromosome
                 << " Weight=" << w
                 << " Value=" << v
                 << " Fitness=" << f
                 << endl;


            if (f > bestFitness) {

                bestFitness = f;
                bestChromosome =
                    chromosome;
            }
        }


        vector<string> newPopulation;


        while (newPopulation.size()
               < POP_SIZE) {

            string parent1 =
                rouletteSelection(
                    population);

            string parent2 =
                rouletteSelection(
                    population);


            auto [child1, child2] =
                crossover(
                    parent1,
                    parent2);


            mutation(child1);
            mutation(child2);


            newPopulation.push_back(
                child1);

            if (newPopulation.size()
                < POP_SIZE) {

                newPopulation.push_back(
                    child2);
            }
        }


        population = newPopulation;
    }


    cout << "\nFinal Result\n";

    cout << "Best Chromosome = "
         << bestChromosome
         << endl;


    char items[] =
        {'A', 'B', 'C', 'D'};


    cout << "Selected Items: ";

    for (int i = 0; i < 4; i++) {

        if (bestChromosome[i] == '1')
            cout << items[i] << " ";
    }

    cout << endl;


    cout << "Total Weight = "
         << totalWeight(
                bestChromosome)
         << " kg"
         << endl;


    cout << "Total Value = "
         << totalValue(
                bestChromosome)
         << endl;


    cout << "Fitness = "
         << bestFitness
         << endl;


    return 0;
}
