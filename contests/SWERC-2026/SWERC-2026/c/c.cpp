// 
#include <bits/stdc++.h>
using namespace std; 
#define forr(i, a, b) for (int i=a; i<b; i++)
#define forn(i, n) forr(i, 0, n)
typedef long long ll;
typedef pair<int, int> ii;

#define debug 1
#define ifd if (debug)

int n, m;
vector<vector<int>> bloques;

int main() {

    cin.tie(0);
    ios_base::sync_with_stdio(false);

	int tC; cin >> tC;
	while (tC--) {
		cin >> n >> m;
		bloques.assign(n, vector<int>(m));
		forn(i, n) {
			forn(j, m) {
				cin >> bloques[i][j];
			}
		}

		vector<int> ans;
		// 1. Busco el tamano del pegue
		vector<int> b = bloques[0];
		int pegue = 0;

		// 2. Empiezo a pegar a partir del primero
		vector<bool> visBloq(70, false), visNum(490 / 2 + 1, false);
		forn(i, m) visNum[b[i]] = true;
		visBloq[0] = true;
		for (int)

		// 3. Duplicar ans
		int var = ans.size();
		forn(i, var) {
			ans.push_back(ans[i]);
		}
		for (int x : ans) cout << x << " ";
		cout << "\n";
	}

	return 0;
}
