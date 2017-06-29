//
// Created by augusto on 14/05/17.
//

#ifndef MUSICAEVOLUTIVA_SOLUTION_H
#define MUSICAEVOLUTIVA_SOLUTION_H

#include "Problem.h"

class Solucao {
public:
    Solucao();
    Solucao(const Problem &p);
    Solucao(const Solucao &mother, const Solucao &father, int cutoff);
    Solucao(vector<int> notas);


    void evaluate(const Problem &p);

    Solucao cruzar(const Solucao &b, const Problem &p);

    Solucao cruzar_media(const Solucao &b, const Problem &p);


    static int binarySearch(const vector<int> &v, int value);

    static bool cmp(const Solucao &a, const Solucao &b);

    void mutar(double sigma);

    void mutar(vector<double> sigma);

    void display();

    vector<int> getNotas() const;



    int getScore() const;

    double get_maxSigma() const;

    int get_notesSize() const;


    bool operator < (const Solucao& b) const;

    void gerarMIDI(string name, string dir);

private:

    static int _notesSize;
    static int _maxSigma;

    Problem p;
    mt19937_64 mt;
    int score;
    vector<int> notas;
};

#endif //MUSICAEVOLUTIVA_SOLUTION_H
