//
// Created by augusto on 27/06/17.
//

#ifndef EVO_AE_H
#define EVO_AE_H

#include <vector>
#include <random>

using namespace std;

#include "Problem.h"
#include "Individuo.h"



class AE {
public:
    AE(Problem &pRight, int tamanho_da_populacao = 100 );
    void run();

    Individuo getMelhorIndividuo();
    void setNumInd(int tam);
    void set_cp(double _cp) { cp = _cp; };
    void set_mp(double _mp) { mp = _mp; };

private:
    void ciclo_evolucionario();
    void evaluation(vector<Individuo> &x);
    void atualizaMelhor(vector<Individuo> &x);

    // de acordo com o terceiro parâmetro, diferentes estratégias de seleção poderão ser utilizadas
    vector<Individuo> selecao(vector<Individuo> &x, int k, int estrategia_de_selecao);
    vector<Individuo> reproducao(vector<Individuo>);

    bool criterio_reinicializacao();
    bool criterio_parada();
    vector<Individuo> elite(vector<Individuo> &x, double porcentagem_de_elitismo);

    Problem instancia;
    vector<Individuo> populacao;
    Individuo melhor;
    double cp;
    double mp;
    int geracao_atual = {0};
    static mt19937_64 generator;

    // este bool definirá se a seleção para reprodução envolverá os pais
    bool competicao_entre_pais_e_filhos;

    // este double definirá a proporção entre pais e filhos
    double proporcao_entre_pais_e_filhos;

};

#endif //EVO_AE_H
