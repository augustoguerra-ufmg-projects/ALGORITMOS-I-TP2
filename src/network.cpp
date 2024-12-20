//=================================================================
// arquivo  : network.cpp
// descricao    : implementacao dos metodos e algoritmos para rede de fluxos
// autor    : Augusto Guerra de Lima augustoguerra@dcc.ufmg.br
// historico    : ultima atualizacao 20241220
//=================================================================
#include<bits/stdc++.h>
#include"../include/network.h"
using namespace std;

// comparacao personalizada para listar as conexoes criticas em ordem
// achei que seria mais facil utilizar uma fila de prioridade para uma ordenacao por heap
// do que criar um algoritmo de ordenacao do zero
// tal personalizacao lista as conexoes com as prioridades solicitadas baseadas em capacidades e vertices
struct compare_critical
{
    bool operator()(const tuple<int,int,int>&a,const tuple<int,int,int>&b) const
    {
        if (get<2>(a) != get<2>(b))return get<2>(a)<get<2>(b);
        
        if (get<0>(a) != get<0>(b))return get<0>(a)>get<0>(b);
        
        return get<1>(a) > get<1>(b);
    }
};

// construtor
graph_c::graph_c(int _V):V(_V),E(0),maxflow(0), total_consumption(0)
{
    adj.resize(V+2);
}

// metodo para adicionar uma aresta ao grafo de intancia para Ford-Fulkerson
void graph_c::add_edge(int u, int v, int capacity, bool is_original)
{
    adj[u].emplace_back(v,0,capacity,is_original);
    E++;
}

// meu metodo para avaliar minimo
// ja que nao e permitido usar a biblioteca algorithms
int my_min(int a, int b)
{
    return(a<b)?a:b;
}

// metodo edmonds_karp para computar o fluxo maximo da rede de fluxo !
int graph_c::edmonds_karp(int s, int t)
{
    maxflow = 0;
    
    // BFS aqui !
    while (true)
    {
        vector<int>parent(V+2,-1);
        vector<int>capacity(V+2,0);
        queue<int>q;

        q.push(s);
        parent[s]=s;
        capacity[s]=INF;

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            for (auto &e:adj[u]) 
            {
                if (parent[e.v]==-1 and e.capacity>e.flux)
                {
                    parent[e.v]=u;
                    capacity[e.v]=my_min(capacity[u], e.capacity - e.flux);

                    if(e.v==t)break;

                    q.push(e.v);
                }
            }
        }

        if (parent[t]==-1)break;

        int path_flow=capacity[t];

        for (int v=t; v!=s; v=parent[v])
        {
            int u=parent[v];

            for (auto &e:adj[u])
            {
                if (e.v==v)
                {
                    e.flux+=path_flow;
                    break;
                }
            }

            for (auto &e:adj[v])
            {
                if (e.v==u)
                {
                    e.flux-=path_flow;
                    break;
                }
            }
        }
        maxflow+=path_flow;
    }
    return(maxflow);
}

// computa a energia faltante
int graph_c::missing()
{
    return(total_consumption-maxflow);
}

// computa a energia perdida
int graph_c::loss()
{
    int sources_capacity=0;
    for(int s:sources)
    {
        for(auto &e:adj[s])
            sources_capacity+=e.capacity;
    }
    return(sources_capacity-maxflow);
}

// lista as conexoes criticas ie arestas saturadas em ordem especificada
void graph_c::critical_edges()
{
    priority_queue<tuple<int,int,int>,vector<tuple<int,int,int>>,compare_critical>pq;

    for(int u=0;u<=V+1;u++)
        for(auto& e:adj[u])
            if(e.is_original and e.flux==e.capacity)
                pq.push(make_tuple(u,e.v,e.capacity));
    
    cout<<pq.size()<<"\n";
    while(!pq.empty())
    {
        tuple<int, int, int> top_edge = pq.top();
        pq.pop();

        int u = get<0>(top_edge);
        int v = get<1>(top_edge);
        int capacity = get<2>(top_edge);
        cout<<u<<" "<<v<<" "<<capacity<<"\n";
    }
}
