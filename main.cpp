#include <algorithm>
#include <iostream>

using namespace std;

#include "Problem.h"
#include "Solution.h"


int main() {
    Problem p;
    vector<Solution> population;

    int genNumber = 0;
    while (true) {
        for (int i = 0; i < 990; i++) {
            population.push_back(Solution(p));
            population[i].evaluate(p);
        }

        sort(population.begin(), population.end(), [](const Solution& x, const Solution &y) { return (x > y); });

        vector<Solution> selection(population.begin(), population.begin()+45);

        cout << "Generation #" << genNumber << endl;
        cout << "Best generation score: " << selection[0].getScore() << endl;

        if (genNumber > 20){
            FILE* file;

            vector<int> notes = selection[1].getNotes();
            selection[1].display();

            file = fopen("notes", "w+b");
            for (int j = 0; j < notes.size(); j++) {
                fwrite(&notes[j], sizeof(int), 1, file);
            }

            fclose(file);
            return 0;
        }

        population.clear();

        for (int i = 0; i < 44; i++) {
            for (int j = i + 1; j < 45; j++){
                population.push_back(Solution::crossover(selection[i], selection[j], p));
            }
        }

        genNumber++;
    }
}