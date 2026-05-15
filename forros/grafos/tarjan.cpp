#include <bits/stdc++.h>
using namespace std;
#define ll long long
// max num de nodos
const ll MAXN =1e5;
// para un nodo i, los adj al mae
vector<int> g[MAXN];     
// seen
bool vis[MAXN];
int low[MAXN], scc[MAXN];  //Inicializar en -1
// idx me dice cuál es el nodo que veo ahorita. 
// Cant me dice cuál es el # de componente conexa que tengo
int idx = 0, cant = 0;
stack<int> s;
void dfs(int v){
	vis[v] = true;

	int tag = low[v] = idx ++;
	s.push(v);
	for(auto x : g[v]){
        // si ese mae ya pertenece a un scc, siga con su vida
		if(vis[x] and scc[x] > -1) continue;
        // si no está seen, haga dfs desde ese mae
		if(not vis[x]) dfs(x);
        // actualice su low
		low[v] = min(low[v], low[x]);
	}
    // si low[v]=vis[v], entonces de fijo el mae es la cabeza de un scc
	if(low[v] == tag){
        // saque del stack hasta llegar a usted 
		while(1){
			int x = s.top(); s.pop();
			scc[x] = cant;
			if(x == v) break;
		}
		cant ++;
	}
}
