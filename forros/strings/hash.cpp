// fumado de https://github.com/mhunicken/icpc-team-notebook-el-vasito/blob/master/strings/hashing.cpp
#include <bits/stdc++.h>
#define ifd if(debug) 
#define forr(i, a, b) for(int i=a; i<b; i++)
#define forn(i, b) forr(i, 0, b)
#define ll long long 
using namespace std;

// OJO: es uno-indexado, pero los queries los responde de manera 0-indexada
struct Hash {
    // usted va a tener:
    // el P primo por el que va a multiplicar las varas
    int P=1777771;
    // el MOD1 y MOD2 por el que va a modular todo
    int MOD[2];
    // el inverso modular de P en MOD 1, y en MOD 2
	int PI[2];
    // el prefixHash del string en MOD1 y el otro en MOD 2 (UNO INDEXADO)
	vector<int> h[2];
    // esto va a ser PI ^ i mod MOD1 y MOD2
    vector<int> pi[2];
	Hash(string& s){
        // usamos el mod1, y el mod2
		MOD[0]=999727999;MOD[1]=1070777777;
        // el inv mult de p en mod1, y el inv mult de p en mod2
		PI[0]=325255434;PI[1]=10018302;
        // métales el tamaño correcto a c/u
		forr(k,0,2)h[k].resize(s.size()+1),pi[k].resize(s.size()+1);
		forr(k,0,2){
            // el hash al inicio es cero
			h[k][0]=0;
            // inv Mult ^ 0 = 1
            pi[k][0]=1;
            // p es la potencia que lleva ahorita
			ll p=1;
            // legalmente, arme el prefix hash
			forr(i,1,s.size()+1){
				h[k][i]=(h[k][i-1]+p*s[i-1])%MOD[k];
				pi[k][i]=(1LL*pi[k][i-1]*PI[k])%MOD[k];
				p=(p*P)%MOD[k];
			}
		}
	}
    // saca el hash de [s, ..., e)
	ll get(int s, int e){
        // PARA MOD1:
        // h0 es el hash hasta e-1, quitándole el hash hasta s-1
		ll h0=(h[0][e]-h[0][s]+MOD[0])%MOD[0];
        // vuélese los ceros del fondo
		h0=(1LL*h0*pi[0][s])%MOD[0];

        // PARA MOD2:
        // h1 es el hash hasta e-1, quitándole el hash hasta s-1
		ll h1=(h[1][e]-h[1][s]+MOD[1])%MOD[1];
        // vuélese los ceros del fondo
		h1=(1LL*h1*pi[1][s])%MOD[1];
		return (h0<<32)|h1;
	}
};
