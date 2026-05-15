#include<bits/stdc++.h>
#define forr(i, a, b) for(int i=a; i<b; i++)
#define forn(i,n) forr(i, 0, n)
#define ll long long
#define ii pair<ll, ll>
#define iii pair<ll, ii>
#define debug 1
#define ifd if(debug)
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	vector<vector<int>> cuerpo(n, vector<int>(m, -1));
	vector<vector<ll>> distance(n, vector<ll>(m, 1e18));


	

	ii cabeza;


	forn(i, k) {
		int a, b; cin >> a >> b;
		a--, b--;
		if (i == 0) cabeza = { a, b };
		cuerpo[a][b] = i;
	}
	distance[cabeza.first][cabeza.second] = 0;


	













}