//
// Created by augusto on 26/06/17.
//

#include "Individuo.h"


Individuo::Individuo(Solucao &_s) {
    s = _s;
    sigma2.resize(s.get_notesSize());

    uniform_real_distribution<double> dist(0, 1);

    for (int i = 0; i < 2; i++) {
        mpp.push_back(dist(mt));
        cpp.push_back(dist(mt));
    }
}

void Individuo::mutacao() {
    uniform_real_distribution<double> distSigma(0, s.get_maxSigma());
    uniform_real_distribution<double> dist(0, 1);
    sigma = distSigma(mt);
    double mutacao = dist(mt);

    for (auto it = sigma2.begin(); it != sigma2.end(); it++) *it = distSigma(mt);

    for (auto it = mpp.begin(); it != mpp.end(); it++) *it = dist(mt);

    for (auto it = cpp.begin(); it != cpp.end(); it++) *it = dist(mt);


    if (mutacao < mpp[0]) s.mutar(sigma);
    else s.mutar(sigma2);

}

Individuo Individuo::cruzar(const Individuo &b, const Problem &p) {
    uniform_real_distribution<double> dist(0, 1);
    double probabilidade = dist(mt);

    Solucao solucaoFilho;

    if (probabilidade < cpp[0]) {
        solucaoFilho = s.cruzar(b.getSolucao(), p);
    }
    else solucaoFilho = s.cruzar_media(b.getSolucao(), p);

    return Individuo(solucaoFilho);
}


Solucao Individuo::getSolucao() const {
    return s;
}