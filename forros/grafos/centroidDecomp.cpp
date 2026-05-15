#include <bits/stdc++.h>
using namespace std;
const int MAXN =1e5;

// la matriz de adj
vector<int> g[MAXN];
int n;

// me dice si el nodo está muerto
bool tk[MAXN];
// el papá en el centroid decomp
int fat[MAXN];
// el tam del subtree
int szt[MAXN];


// calcule el size del subtree desde x, sabiendo que su papá es f
// ojo que es solo el subtree desde x que no pasa ni por su papá ni por nadie dead
int calcsz(int x, int f){
	szt[x]=1;
	for(auto y:g[x])if(y!=f&&!tk[y])szt[x]+=calcsz(y,x);
	return szt[x];
}

// usted está en el nodo x, con papá =f, sz = el size del current component (?) 
void cdfs(int x=0, int f=-1, int sz=-1){ // O(nlogn)
	
	if(sz<0)sz=calcsz(x,-1);
	// para sus adj que no estén taken
	for(auto y:g[x])if(!tk[y]&&szt[y]*2>=sz){
		// esta vara es solo para que después no se meta a este mae
		szt[x]=0;
		// si ese y existía, entonces de fijo x no es centroide, 
		cdfs(y,f,sz);return;
	}
	// si no existía ningún y, de fijo x es centroide. Haga lo que ocupe con ese dato
	tk[x]=true;
	// guarde que su papá en el centroid-decomp tree es f
	fat[x]=f;
	// repita la vara para todos los otros nodos
	for(auto y:g[x])if(!tk[y])cdfs(y,x);
}
void centroid(){memset(tk,false,sizeof(tk));cdfs();}