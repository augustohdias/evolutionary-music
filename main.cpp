#include <iostream>
#include <random>
#include <algorithm>

using namespace std;


#include "Problem.h"
#include "Solucao.h"



int main() {
    Problem keyNote;
    vector<Solucao> population;
    vector<Solucao> filhos;
    vector<Solucao> nextGen;

    int cont = 0;

    for (int i = 0; i < 100; i++) population.push_back(Solucao(keyNote));

    int gen = 0;
    while (gen++ < 100) {
        cout << endl << endl << "Generation: " << gen << endl;

        random_device rd;
        mt19937_64 mt(rd());
        uniform_real_distribution<double> distribution(0, 1);

        double probability = distribution(mt);

        if (probability <= 0.95) { // Crossover
            cout << "Crossover" << endl;
            for (int i = 1; i < population.size(); i++) {
                filhos.push_back(Solucao::cruzar(population[i - 1], population[i], keyNote));
                filhos.push_back(Solucao::cruzar(population[i], population[i - 1], keyNote));
            }
        }
        else {
            cout << "Mutation" << endl;
            cont++;
            for (auto a : population) a.mutar();
            continue;
        }

        sort(nextGen.begin(), nextGen.end(), Solucao::cmp);
        sort(population.begin(), population.end(), Solucao::cmp);

        for (int i = 0; i < (population.size()/2); i++) {
            nextGen.push_back(population[i]);
            nextGen.push_back(filhos[i]);
        }

        population = nextGen;
        nextGen.clear();
    }
}
