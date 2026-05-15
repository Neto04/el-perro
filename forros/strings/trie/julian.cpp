#include <bits/stdc++.h> 
#define ll long long
#define forr(i, a, b) for(int i=a; i<b; i++)
#define forn(i,n) forr(i, 0, n)
#define debug 1
#define ifd if(debug)
using namespace std;

struct Trie {
	Trie* hijos[26]; // map<char,Trie> hijos
	int words,pref;
	Trie(): words(0), pref(0){
for(int i = 0; i < 26; i++) hijos[i] = NULL;}};
        
void add(Trie* node, string word, int k) {
	if(k == word.size()){
		node->words++; node->pref++;}
	else{
		node->pref++; int ind = (int)(word[k] - 'a');
		if(node->hijos[ind] == NULL) {
			Trie* v = new Trie; node->hijos[ind] = v;
			add(node->hijos[ind], word, k+1);}
		else add(node->hijos[ind], word, k+1);}}
int search(Trie* node, string word, int k){
	if(k == word.size()) return (node->words);
	int ind = (int)(word[k] - 'a');
	if(node->hijos[ind] == NULL) return (0);
	else return search(node->hijos[ind], word, k+1);}




int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);
}