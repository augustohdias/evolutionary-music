//
// Created by augusto on 14/05/17.
//

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

#include "Solucao.h"
#include "include/MidiFile.h"

int Solucao::_notesSize = 64;
int Solucao::_maxSigma = 4;

//! Constructors
Solucao::Solucao() {}

Solucao::Solucao(const Problem &p) {
    random_device rd;
    mt.seed(rd());
    uniform_int_distribution<int> distribution(60, 71);

    for (int i = 0; i < _notesSize; i++) {
        notas.push_back(distribution(mt));
    }
    evaluate(p);
}

Solucao::Solucao(const Solucao &mother, const Solucao &father, int cutoff) {
    for (int i = 0; i < _notesSize; i++) {
        if (i < cutoff)
            notas.push_back(mother.getNotas()[i]);
        else
            notas.push_back(father.getNotas()[i]);
    }
}

//! AE Functions
void Solucao::evaluate(const Problem &p) {
    int key = p.getKey();
    vector<int> majorScale = { 0, 2, 4, 5, 7, 9, 11, 12 };

    for (auto i : majorScale) {
        i += key;
    }

    score = 0;
    vector<int> dissonances;
    for (int i = 0; i < notas.size(); i++) {
        if (find(majorScale.begin(), majorScale.end(), notas[i]) != majorScale.end()) {
            score += 40;
        }
        else if (notas[i] >= 0) {
            score -= 20;
            dissonances.push_back(i);
        }
    }

    for (int i = 0; i < dissonances.size(); i++) {
        if (abs(majorScale[dissonances[i] - 1] - majorScale[dissonances[i] + 1]) == 1) {
            score += 20;
        }
        else {
            score -= 20;
        }
    }
}

bool Solucao::cmp(const Solucao &a, const Solucao &b) {
    return (b < a);
}

Solucao Solucao::cruzar(const Solucao &b, const Problem &p) {
    random_device rd;
    mt.seed(rd());
    uniform_int_distribution<int> distribution(-1, _notesSize);
    int cutoff = distribution(mt);

    Solucao filho(*this, b, cutoff);
    filho.evaluate(p);

    return filho;
}

Solucao Solucao::cruzar_media(const Solucao &b, const Problem &p) {
    vector<int> v;

    for (int i = 0; i < _notesSize; i++)
        v.push_back((getNotas()[i]*2 + b.getNotas()[i])/3);


    Solucao filho(v);
    filho.evaluate(p);

    return filho;
}

int Solucao::binarySearch(const vector<int> &v, int value) {
    int first = 0;
    int last = (int) v.size() - 1;
    int middle = (first+last)/2;

    while (first <= last) {
        if (v[middle] < value)
            first = middle + 1;
        else if (v[middle] >= value && v[middle-1] < value) {
            return middle;
        }
        else
            last = middle - 1;

        middle = (first + last)/2;
    }
    if (first > last)
        return 0;
}

void Solucao::mutar(double sigma) {
    random_device rd;
    mt.seed(rd());
    uniform_real_distribution<double> mutationProb(0, 1);
    uniform_real_distribution<double> mutationFactor(-1, 1);

    double factor = 0;
    double v[] = {-1, -14/15.0, -12/15.0, -9/15.0, -5/15.0, 0, 5/15.0, 9/15.0, 12/15.0, 14/15.0, 1};

    for (int i = 0; i < notas.size(); i++) {

        if (mutationProb(mt) <= 1/(double (notas.size()))) {

            factor = (mutationFactor(mt)*sigma)/_maxSigma;

            int k = 1;
            while (factor >= v[k-1] && factor < v[k]) k++;
            k = k - 5;

            notas[i] += k;
        }
    }
}

void Solucao::mutar(vector<double> sigma) {
    random_device rd;
    mt.seed(rd());
    uniform_real_distribution<double> mutationProb(0, 1);
    uniform_real_distribution<double> mutationFactor(-1, 1);

    double factor = 0;
    double v[] = {-1, -14/15.0, -12/15.0, -9/15.0, -5/15.0, 0, 5/15.0, 9/15.0, 12/15.0, 14/15.0, 1};

    for (int i = 0; i < notas.size(); i++) {

        if (mutationProb(mt) <= 1/(double (notas.size()))) {

            factor = (mutationFactor(mt)*sigma[i])/_maxSigma;

            int k = 1;
            while (factor >= v[k-1] && factor < v[k]) k++;
            k = k - 5;

            notas[i] += k;
        }
    }
}

void Solucao::display() {
    for (int i = 0; i < _notesSize; i++) {
        if (i % 4 == 0 && i > 0) {
            cout << "   ";
        }
        if (i % 8 == 0 && i > 0) {
            cout << endl;
        }
        if (notas[i] < 10)
            cout << " " << notas[i] << " ";
        else
            cout << notas[i] << " ";
    }
}

int Solucao::getScore() const {
    return score;
}



double Solucao::get_maxSigma() const {
    return _maxSigma;
}

int Solucao::get_notesSize() const {
    return _notesSize;
}

vector<int> Solucao::getNotas() const {
    return notas;
}





bool Solucao::operator < (const Solucao& b) const {
    return (getScore() < b.getScore());
}

void Solucao::gerarMIDI(string name, string dir) {
    MidiFile outputfile;
    outputfile.absoluteTicks();
    outputfile.addTrack();
    vector<uchar> midievent;
    midievent.resize(3);
    int tpq = 120;
    outputfile.setTicksPerQuarterNote(tpq);

    int actiontime = 0;
    midievent[2] = 64;
    for (auto a : notas) {
        midievent[0] = 0x90;
        midievent[1] = uchar(a + 60);
        outputfile.addEvent(1, actiontime, midievent);
        actiontime += tpq;
        midievent[0] = 0x80;
        outputfile.addEvent(1, actiontime, midievent);

    }

    outputfile.sortTracks();
    outputfile.write(name);
}

