// 
#include <bits/stdc++.h>
using namespace std; 
#define forr(i, a, b) for (int i=a; i<b; i++)
#define forn(i, n) forr(i, 0, n)
typedef long long ll;
typedef pair<int, int> ii;

#define debug 1
#define ifd if (debug)
vector<int> a, b;
vector<vector<bitset<2>>> dp, seen;
int n, m;



bool solve(int i, int j, int k) {
	if (seen[i][j][k]) return dp[i][j][k];
	seen[i][j][k] = 1;



	
	// si ya se acabaron las de b, revise si tambien acabaron las de a
	if (j == m) {
		// si se acabo a
		if (i == n) return dp[i][j][k] = 1;
		// si lo ultimo que paso fue que alguien chupo
		if (k == 0) return dp[i][j][k] = 1;
		return dp[i][j][k]=0;
	}
	// si termino con a y no b, rip
	if (i == n) return dp[i][j][k] = 0;
	int ans1 = 0, ans2 = 0, ans3 = 0;
	// se lo queda
	if (a[i] == b[j]) ans1 = solve(i + 1, j + 1, 1);
	// chupa
	int nxt = b[j] + i;
	if (nxt <= n) ans2 = solve(nxt, j + 1, 0);
	if (!k) ans3 = solve(i + 1, j, 0);
	return dp[i][j][k] = ans1 or ans2 or ans3;
}



int main() {

    cin.tie(0);
	ios_base::sync_with_stdio(false);
	string ans[2] = { "NO", "YES" };
	int tC; cin >> tC;
	while (tC--) {
		cin >> n >> m;
		dp.clear(), seen.clear(), a.clear(), b.clear();
		dp.resize(n + 1), seen.resize(n + 1), a.resize(n), b.resize(m);
		forn(i, n) cin >> a[i];
		forn(i, m) cin >> b[i];
		forn(i, n + 1) {
			dp[i].resize(m + 1), seen[i].resize(m + 1);
			
		}
		
		cout << ans[solve(0, 0, 1)] << "\n";
	}

}
