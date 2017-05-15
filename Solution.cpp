//
// Created by augusto on 14/05/17.
//

#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

using namespace std;

#include "Solution.h"

default_random_engine Solution::gen;
int Solution::_notesSize = 64;

//! Constructors
Solution::Solution(Problem &p) {
    gen.seed((unsigned) chrono::system_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> distribution(-1, 24);

    for (int i = 0; i < _notesSize; i++) {
        notes.push_back(distribution(this->gen));
    }

    this->evaluate(p);
}

Solution::Solution(Solution &mother, Solution &father, int cutoff) {
    for (int i = 0; i < _notesSize; i++) {
        if (i < cutoff)
            notes.push_back(mother.getNotes()[i]);
        else
            notes.push_back(father.getNotes()[i]);
    }
}

//! AE Functions
void Solution::evaluate(Problem &p) {
    int key = p.getKey();
    vector<int> majorScale = { 0, 2, 4, 5, 7, 9, 11, 12 };

    for (auto i : majorScale) {
        i += key;
        if (i > 12) i -= 12;
    }


    score = 0;
    vector<int> dissonances;
    for (int i = 0; i < notes.size(); i++) {
        if (find(majorScale.begin(), majorScale.end(), notes[i]) != majorScale.end()) {
            score += 100;
        }
        else if (notes[i] >= 0) {
            score -= 50;
            dissonances.push_back(i);
        }
    }

    for (int i = 0; i < dissonances.size(); i++) {
        if (abs(majorScale[dissonances[i] - 1] - majorScale[dissonances[i] + 1]) == 1) {
            score += 50;
        }
        else {
            score -= 50;
        }
    }
}

Solution Solution::crossover(Solution &mother, Solution &father, Problem &p) {
    gen.seed((unsigned) chrono::system_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> distribution(-1, _notesSize);
    int cutoff = distribution(gen);
    Solution son(mother, father, cutoff);
    son.evaluate(p);
    return son;
}

void Solution::mutation() {

}

void Solution::display() {
    for (int i = 0; i < _notesSize; i++) {
        if (i % 4 == 0 && i > 0) {
            cout << "   ";
        }
        if (i % 8 == 0 && i > 0) {
            cout << endl;
        }
        if (notes[i] < 10)
            cout << " " << notes[i] << " ";
        else
            cout << notes[i] << " ";
    }
}

int Solution::getScore() const {
    return score;
}

vector<int> Solution::getNotes() const {
    return notes;
}

bool Solution::operator > (const Solution& b) const {
    return (getScore() > b.getScore());
}
