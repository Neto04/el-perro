// 
#include <bits/stdc++.h>
using namespace std; 
#define forr(i, a, b) for (int i=a; i<b; i++)
#define forn(i, n) forr(i, 0, n)
#define sz(c) ((int)c.size())
#define zero(v) memset(v, 0, sizeof(v))
#define forall(it, v) for (auto it=v.begin(); it!=v.end(); ++it)
#define pb push_back
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> ii;
#define dforn(i, n) for (int i=n-1; i>=0; i--)
#define dprint(v) cout<<#v"="<<v<<endl
const int MAX=1e6+5;

#define debug 1
#define ifd if (debug)
const int MOD =1e9+7;
vector<ll> f(1e6+5);
vector<ll> I(1e6+5);
ll exp(ll base, ll exp) {
    ll r=1;
    while (exp) {
        if (exp%2) r=r*base%MOD;
        base=base*base%MOD;
        exp/=2;
    }
    return r;
}
ll choose (int a, int b) {
    return (((f[a]*I[b])%MOD)*I[a-b])%MOD;
}

int main() {

    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int n; cin>>n;
    f[0]=1;
    forr(i, 1, MAX) f[i]=(f[i-1]*i)%MOD;
    I[MAX-1] = exp(f[MAX-1], MOD-2);
    for(ll i=MAX-1; i>0; i--) I[i-1]=(I[i]*i)%MOD;

}
