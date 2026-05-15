// trie plagiado de Teruel, modificado
#include <bits/stdc++.h> 
#define ll long long
#define forr(i, a, b) for(int i=a; i<b; i++)
#define forn(i,n) forr(i, 0, n)
#define debug 1
#define ifd if(debug)
using namespace std;


struct node {
    // nxt[x] me dice el nodo al que voy si
    // estoy en mi nodo actual y me encuentro la letra x
    unordered_map<int, int> nxt;
    // me dice cuántas letras tiene de hijos x
    // OJO: la raíz tiene tam =0, y finales =0
    int tam;
    // me dice cuántos maes terminan en ese nodo
    int finales;
    node() : tam(0), finales(0) {}
};


bool isFinal(node& nodo) {return nodo.finales==nodo.tam;}
void Add(vector <node> &trie, string &s) {
    int curr = 0;
    for (int i = 0; i < s.size(); i++) {
        int c = s[i];
        if (!trie[curr].nxt.count(c)) {
            trie[curr].nxt[c] = trie.size();
            trie.emplace_back();
        }
        curr = trie[curr].nxt[c];
        trie[curr].tam++;
    }
    trie[curr].finales++;
}

// usted sabe que todas las letras anteriores estaban, revise si la i-esima está
int search(vector<node>& trie, int cN, string & s, int i) {
    // si ya llegó al final de esa palabra, tire cuántas veces ha metido a ese mae
    if (i==s.size()) return trie[cN].finales;
    int c = s[i];
    // de fijo si usted no era siguiente de la letra anterior, rip
    if (!trie[cN].nxt.count(c)) return 0;
    return search(trie, trie[cN].nxt[c], s, i+1);
    
}
// me retorna cuántas veces aparece un string s en el trie
int search(vector<node>& trie, string & s) {
    return search(trie, 0, s, 0);
}


// está en el nodo cN a punto de moverse a la letra i del string s
// me dice si, después de quitar la letra i del string s, el nodo cN quedó vacío
bool quitar(vector<node>& trie, int cN, string & s, int i) {
    // si ya llegó al final de la palabra, todo bien, solo retorne si el nodo ahora quedó vacío o no
    if (i==s.size()) {
        trie[cN].tam--;
        trie[cN].finales--;
        // retorne si queda o no vacío
        return (trie[cN].tam==0 and trie[cN].finales==0);
    }

    int c=s[i];
    int sig=trie[cN].nxt[s[i]];
    // intente quitar la siguiente letra, si esa vara queda vacía, bórrela
    if (quitar(trie, sig, s, i+1)) trie[cN].nxt.erase(c);
    // retorne si (usted ya no tiene hijos Y usted no es final de nadie)
    return trie[cN].tam==0 and trie[cN].finales==0;
}


bool quitar(vector<node>& trie, string& s) {
    if (!search(trie, s)) return false;
    return quitar(trie, 0, s, 0);
}





int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);


    int n; cin>>n;
    vector<string> v(n);
    vector<node> trie(1);

    forn(i, n) {
        cin>>v[i];
        Add(trie, v[i]);
    }

    int q; cin>>q;
    while (q--) {
        int op; cin>>op;
        string s; cin>>s;
        if (op==1) cout<<search(trie, s)<<endl;
        else if (op==2) Add(trie, s);
        else {
            cout<<quitar(trie, s)<<endl;
        }
        
    }

}