// 
#include <bits/stdc++.h>
#define ll long long
#define debug 0

using namespace std; 

ll n;

ll raizQ(ll a) {
    long long x = sqrt(a) + 2;
    while (x * x > a) x--;

    return x;
}

// genera la mitad de los divisores de un valor d
// (todos los leq a sqrt(d))
void divisores(ll d, vector<ll> &v) {
    ll s=raizQ(d);

    for(ll i = 1;i <= s;i++) {
        // no estoy muy seguro de para qué es esta línea
        if (d/i<n) break;
        if (d%i==0) {
            
            v.push_back(i);
        }
    }
}


int main() {

    cin.tie(0);
    ios_base::sync_with_stdio(false);

    vector<ll> v; 
    ll d; cin>>d;
    divisores(d, v);
    cout<<"divisores de "<<d<<":\n";
    for (int n:v) cout<<n<<endl;


}
