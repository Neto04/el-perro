// 
#include <bits/stdc++.h>
#define ll long long
#define debug 0

using namespace std; 

ll raizQ(ll n) {
    return n;
}


ll numDivisors(ll n, vector<ll>& primes, vector<bool>& isPrime) {

    ll ans=1;
    for (ll p:primes) {
        if (p*p*p>=n) break;
        ll count=1;
        while((n%p)==0) {
            n=n/p;
            count++;
        }
        ans*=count;
    }

    if (isPrime[n]) ans*=2;
    else if (isPrime[raizQ(n)]) ans*=3;
    else ans*=4;


}


int main() {

    cin.tie(0);
    ios_base::sync_with_stdio(false);

    /**
     * @brief la función retorna el # de divisores de n
     * Complejidad: O(n^(1/3))
     * 
     * @param n 
     * @param primes los primos de 1 a 1e6 
     * @return ll 
     */

    
    // no lo voy a poner aquí, pero asumimos que primes tiene todos los primos de 1 a 1e6
    



}
