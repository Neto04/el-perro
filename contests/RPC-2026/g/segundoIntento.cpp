// 
#include <bits/stdc++.h>
using namespace std; 
#define forr(i, a, b) for (int i=a; i<b; i++)
#define forn(i, n) forr(i, 0, n)
typedef long long ll;
typedef pair<int, int> ii;

#define debug 0
#define ifd if (debug)








int main() {

    cin.tie(0);
    ios_base::sync_with_stdio(false);
    ll n, m; cin>>n>>m;
    vector<vector<ll>> v(n, vector<ll> (m));
    forn(i, n) forn(j,m) cin>>v[i][j];
    set<ii> altos;
    ll ans =0;
    for(int j=m-1; j>=0; j--) {
        ll cUp=-1, cDown=-1;
        forn(i, n) {
            if (v[i][j]) {
                if (cUp==-1) cUp=i;
                cDown=i;
            }
        }
        // si no hay nadie en esa columna, no importa
        if (cUp==-1) continue;
        
        if (altos.empty()) {
            ans++;
            altos.insert({cUp, j});
        }
        
        auto it =altos.lower_bound({cDown, -1});
        if (it==altos.end()) ans++;
        else altos.erase(it);
        altos.insert({cUp, j});
    }
    cout<<ans<<"\n";


}
