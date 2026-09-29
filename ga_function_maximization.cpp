#include <bits/stdc++.h>
using namespace std;

const int POP_SIZE = 6;
const int GENERATIONS = 20;
const double MUTATION_RATE = 0.05;


int binaryToDecimal(string chromosome) {

    int value = 0;

    for (char bit : chromosome) {

        value =
            value * 2 +
            (bit - '0');
    }

    return value;
}


int fitness(string chromosome) {

    int x = binaryToDecimal(chromosome);

    return 15 * x - x * x;
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

    int r = rand() % totalFitness;

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

            if (chromosome[i] == '0')
                chromosome[i] = '1';
            else
                chromosome[i] = '0';
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

            int x =
                binaryToDecimal(
                    chromosome
                );

            int f =
                fitness(chromosome);

            cout << chromosome
                 << " x=" << x
                 << " fitness=" << f
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

    cout << "Best x = "
         << binaryToDecimal(
                bestChromosome)
         << endl;

    cout << "Maximum Fitness = "
         << bestFitness
         << endl;

    return 0;
}
