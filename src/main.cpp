//=================================================================
// arquivo  : main.cpp
// descricao    : processa entrada do tp2
// autor    : Augusto Guerra de Lima augustoguerra@dcc.ufmg.br
// historico    : ultima atualizacao 20241220
//=================================================================
#include<bits/stdc++.h>
#include"../include/network.h"
using namespace std;

int main()
{
    int V,E;
    cin>>V>>E;

    graph_c G(V);
    int source=0;
    int sink=V+1;

    for(int i=0;i<V;i++)
    {
        int v,consumption;
        cin>>v>>consumption;

        if(consumption==0)//liga da source
        {
            G.sources.push_back(v);
            G.add_edge(source,v,INF,false);
        }
        else//liga na sink
        {
            G.total_consumption+=consumption;
            G.add_edge(v,sink,consumption,false);
        }
    }

    for(int i=0;i<E;i++)
    {
        int u,v,capacity;
        cin>>u>>v>>capacity;
        G.add_edge(u,v,capacity,true);
    }

    cout<<G.edmonds_karp(source,sink)<<"\n";
    cout<<G.missing()<<"\n";
    cout<<G.loss()<<"\n";
    G.critical_edges();

    return(0);
}