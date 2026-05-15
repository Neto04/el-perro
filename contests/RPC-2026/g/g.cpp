// 
#include <bits/stdc++.h>
using namespace std; 
#define forr(i, a, b) for (int i=a; i<b; i++)
#define forn(i, n) forr(i, 0, n)
typedef long long ll;
typedef pair<int, int> ii;

#define debug 0
#define ifd if (debug)

vector<vector<ii>> mover;
vector<vector<ll>> dp;
vector<vector<ll>> seen;
vector<vector<ll>> v;
ll n, m;


ll solve (ll i, ll j) {
    ifd cout<<"solve "<<i<<", "<<j<<endl;
    if (seen[i][j]) return dp[i][j];
    seen[i][j] = 1;
    ll& ans = dp[i][j] = v[i][j];

    // del final no va a ningún lado
    if (i==n-1 and j==m-1) {
        mover[i][j]={-1, -1};
        return ans;
    }
    // vea a ver qué pex si va abajo
    ll x1 = -1; ii cM = {i, j+1};
    ll x2 = -1; 
    if (j<m-1) x2=solve(i, j+1);
    
    if (i<n-1) x1=solve(i+1, j);
    // vea a ver qué pex si va a la derecha
    if (x2<x1) cM = {i+1, j};

    mover[i][j]=cM;
    return ans+=max(x1, x2);
}

void limpie( ){
    ll cI=0, cJ=0;
    while (cI!=-1 and cJ!=-1) {
        v[cI][cJ]=0;
        tie(cI, cJ)=mover[cI][cJ];
    }
}





int main() {

    cin.tie(0);
    ios_base::sync_with_stdio(false);
    cin>>n>>m;
    v.resize(n); forn(i, n) v[i].resize(m);
    ll vivos=0;
    forn(i, n) forn(j,m) {
        cin>>v[i][j];
        vivos+=v[i][j];
    }
    ll ans=0;
    while (vivos) {
        ifd cout<<"VIVOS = "<<vivos<<endl;
        ans++;
        dp.clear(), seen.clear(), mover.clear();
        dp.resize(n), seen.resize(n), mover.resize(n);
        forn(i, n) dp[i].resize(m), seen[i].resize(m), mover[i].resize(m);
        ifd cout<<"holi"<<endl;
        vivos-=solve(0, 0);
        limpie();
    }


    cout<<ans<<"\n";

}
