// 
#include <bits/stdc++.h>
#define ll long long
#define debug 0

using namespace std; 

bool prime (ll p) {
    if (p<2) return false;
    for (ll x=2; x*x<=p; x++) if (p%x==0) return false;
    return true;
} 


int main() {

    cin.tie(0);
    ios_base::sync_with_stdio(false);


}
