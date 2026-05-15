// código fumado de Teruel
#include <bits/stdc++.h> 
#define ll long long
#define forr(i, a, b) for(int i=a; i<b; i++)
#define forn(i,n) forr(i, 0, n)
#define debug 1
#define ifd if(debug)
using namespace std;
vector<int> freq(3*1e6);
int maxFreq=0;
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
        freq[curr]++;
        maxFreq=max(maxFreq, freq[curr]);
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
int search(node& cN, string & s, int i) {
    // si ya llegó al final de esa palabra, tire cuántas veces ha metido a ese mae
    if (i==s.size()) return cN.finales;
    
    if (cN.nxt.count(s[i])) {
        
    }
}
// me retorna cuántas veces aparece un string s en el trie
int search(vector<node>& trie, string & s) {
    return search(trie[0], s, 0);
}



int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);


    int n; cin>>n;

    vector<node> trie(1);
    // usted ocupa meterle un caracter extra de final de palabra
    // al end de cada palabra
    forn(i, n) {
        cin>>v[i];
        v[i];
        Add(trie, v[i]);
    }
    int n; cin>>n;
    forn(i, n) {
        string s; cin>>s;
        
    }




}