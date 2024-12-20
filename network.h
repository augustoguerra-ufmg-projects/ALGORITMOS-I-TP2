//=================================================================
// arquivo  : network.h
// descricao    : cabecalho para implementacao da rede de fluxo
// autor    : Augusto Guerra de Lima augustoguerra@dcc.ufmg.br
// historico    : ultima atualizacao 20241220
//=================================================================
#ifndef NETWORK_H
#define NETWORK_H

#include<bits/stdc++.h>
using namespace std;

const int INF=0x3f3f3f3f;

// classe para determinar as arestas
class edge_c
{
public:
    int v;
    int flux;
    int capacity;
    bool is_original;

    edge_c(int _v, int _flux, int _capacity, bool _is_original)
        : v(_v), flux(_flux), capacity(_capacity), is_original(_is_original){}
};

// classe para determinar a rede de fluxo
class graph_c
{
public:
    int V,E;
    int maxflow, total_consumption;

    vector<int>sources;

    vector<vector<edge_c>>adj;

    graph_c(int _V);
    ~graph_c(){}

    void add_edge(int u, int v, int capacity, bool is_original);
    
    int edmonds_karp(int s, int t);
    int missing();
    int loss();
    void critical_edges();
};

#endif