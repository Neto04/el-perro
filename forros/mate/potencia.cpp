// 
#include <bits/stdc++.h>
#define ll long long
#define debug 0

using namespace std; 


ll exp(ll base, ll exp, ll mod) {
    ll r=1;
    while (exp) {
        if (exp%2) r=r*base%mod;
        base=base*base%mod;
        exp/=2;
    }
    return r;
}

int main() {

    cin.tie(0);
    ios_base::sync_with_stdio(false);
    

}
