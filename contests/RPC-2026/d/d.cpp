// 
#include <bits/stdc++.h>
using namespace std; 
#define forr(i, a, b) for (int i=a; i<b; i++)
#define forn(i, n) forr(i, 0, n)
typedef long long ll;
typedef pair<int, int> ii;

#define debug 1
#define ifd if (debug)

int main() {

    cin.tie(0);
    ios_base::sync_with_stdio(false);
    ll h, m; cin>>h>>m;
    m+=h*60;
    ll n; cin>>n;
    vector<ii> v(n);
    ll cSum=0;
    forn(i, n) {
        ll x, y; cin>>x>>y;
        v[i]={cSum+x, y};
        cSum+=x;
    }


    ll cI=0, ans =0;
    forn(i, m) {
        if (i==v[cI].first) {
            cI++;
            if (cI==n) break;
        }
        ans+=v[cI].second;
    }

    cout<<ans<<"\n";




}
