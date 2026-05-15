// 
#include <bits/stdc++.h>
using namespace std; 
#define forr(i, a, b) for (int i=a; i<b; i++)
#define forn(i, n) forr(i, 0, n)
typedef long long ll;
typedef pair<int, int> ii;

#define debug 0
#define ifd if (debug)
ll NN=105;
const ll MOD = 1e9+7;
vector<vector<ll>> res(NN, vector<ll> (NN));
 
void mul(vector<vector<ll>>&a, vector<vector<ll>>& b){ 
    vector<vector<ll>> tmp(NN, vector<ll> (NN));
    forn(i, NN) forn(j, NN) forn(k, NN) tmp[i][j]=(tmp[i][j]+(a[i][k]*b[k][j])%MOD)%MOD;
    forn(i, NN) forn(j, NN) a[i][j]=tmp[i][j]; 
}
 
void powmat(vector<vector<ll>> &a, ll exp){
    ifd cout<<"res: "<<endl; 
    forn(i, NN) {
        forn(j, NN) {
            res[i][j]=(i==j);
            ifd cout<<res[i][j]<<" ";
        }
        ifd cout<<endl;
    }
 
    while(exp){
        ifd cout<<"exp = "<<exp<<endl;
        if(exp&1) mul(res, a), exp--;
        else mul(a, a), exp/=2;
    }
}
 




int main() {

    cin.tie(0);
    ios_base::sync_with_stdio(false);
    ll n, m; cin>>n>>m;

    if (n==1) {
        cout<<m<<endl;
        return 0;
    }
    vector<vector<ll>> v(105, vector<ll> (105));
    forr(i,1, m+1) forr(j, 1, m+1) v[i][j] = (gcd(i, j)==1);
    powmat(v, n-1);

    ll ans =0;
    forr(i, 1, m+1) forr(j, 1, m+1) ans=(ans+res[i][j])%MOD;
    cout<<ans<<"\n";
}
