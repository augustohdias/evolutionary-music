//
// Created by augusto on 26/06/17.
//

#ifndef EVO_INDIVIDUO_H
#define EVO_INDIVIDUO_H

#include <vector>
#include <random>

using namespace std;

#include "Solucao.h"

class Individuo {
    Individuo(Solucao &s);

    void mutacao();
    Individuo cruzar(const Individuo &b, const Problem &p);

    Solucao getSolucao() const;
private:
    Solucao s;

    double sigma;
    vector<double> sigma2;

    vector<double> cpp;
    vector<double> mpp;
    vector<double> smpp;

    mt19937_64 mt;
};


#endif //EVO_INDIVIDUO_H
