#include<bits/stdc++.h>
#define forr(i, a, b) for(int i=a; i<b; i++)
#define forn(i,n) forr(i, 0, n)
#define ll long long
using u64 = uint64_t;
#define ii pair<ll, ll>
#define iii pair<ll, ii>
#define debug 0
#define ifd if(debug)
using namespace std;


int n, m;

bool valid(int i, int j) {
	return i>=0 and i<n and j>=0 and j<m;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int k;
	cin >> n >> m >> k;
	
	vector<vector<int>> cuerpo(n, vector<int>(m, -1)), seen(n, vector<int> (m, 0)), caca(n, vector<int> (m, 0));
	vector<vector<ll>> distance(n, vector<ll>(m, 1e18));

	
	ii cabeza;
	forn(i, k) {
		int a, b; cin >> a >> b;
		a--, b--;
		if (i == 0) cabeza = { a, b };
		cuerpo[a][b] = i;
	}
	forn(i, n) forn(j, m) {
		char c; cin>>c;
		caca[i][j] = (c!='.');
	}



	distance[cabeza.first][cabeza.second] = 0;
	ifd cout<<"dist cabeza = "<<distance[cabeza.first][cabeza.second]<<endl;
	int iDelta[4] = {-1, 1, 0,0}, jDelta[4] = {0, 0, -1, 1};

	priority_queue<iii> pq;
	pq.push({0, cabeza});
	while (!pq.empty()) {
		int a, b; tie(a, b) = pq.top().second; pq.pop();
		ifd cout<<"saco "<<a<<", "<<b<<endl;
		ifd cout<<"distance["<<a<<"]"<<"["<<b<<"] = "<<distance[a][b]<<endl;
		if (seen[a][b]) continue;
		seen[a][b] = true;
		if (caca[a][b]) continue;
		forn(_, 4) {
			int aN = a+iDelta[_], bN = b+jDelta[_];
			if (!valid(aN, bN)) continue;
			ifd cout<<"vea que "<<aN<<", "<<bN<<" es adj a "<<a<<", "<<b<<endl;
			int w = 1;
			if (cuerpo[aN][bN]>=0) {
				ifd cout<<"vea que "<<aN<<", "<<bN<<" es cuerpo"<<endl;
				// vea que para quitar todos los tuquitos (incluyendo a ese mae), faltan n-cuerpo[aN][bN]
				if (k-cuerpo[aN][bN] > distance[a][b]+1) w = k-cuerpo[aN][bN]-distance[a][b];
				ifd cout<<"distance["<<a<<"]"<<"["<<b<<"] + "<<w<<" = "<<distance[a][b]+w<<endl;
			}
			if (distance[a][b]+w<distance[aN][bN]) {
				distance[aN][bN] = distance[a][b]+w;
				pq.push({-distance[aN][bN], {aN, bN}});
			}
 			
		}
	}
	u64 ans =0;
	forn(i, n) forn(j, m) if(!caca[i][j] and seen[i][j]) {
		ifd cout<<"vea que dist "<<i<<", "<<j<<" = "<<distance[i][j]<<endl;
		u64 curr = distance[i][j];
		ans +=curr*curr;
	}
	
	cout<<ans<<"\n";
	













}