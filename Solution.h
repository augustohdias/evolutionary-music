//
// Created by augusto on 14/05/17.
//

#ifndef MUSICAEVOLUTIVA_SOLUTION_H
#define MUSICAEVOLUTIVA_SOLUTION_H

#include "Problem.h"

class Solution {
public:
    Solution(Problem &p);
    Solution(Solution &mother, Solution &father, int cutoff);

    void evaluate(Problem &p);

    static Solution crossover(Solution &mother, Solution &father, Problem &p);

    void mutation();

    void display();

    vector<int> getNotes() const;

    int getScore() const;

    bool operator > (const Solution& b) const;

private:

    static int _notesSize;
    static default_random_engine gen;
    int score;
    vector<int> notes;
};

#endif //MUSICAEVOLUTIVA_SOLUTION_H
