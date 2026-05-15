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

const ll maxn = 60;
// OJO: para que esto sirva ocupa:
// 1. que maxn escojo maxn/2 quepa en un ll
// 2. que maxn x maxn queepa en memoria
ll C[maxn + 1][maxn + 1];

ll choose (ll a, ll b) {
    if (a<b) return 0;
    return C[a][b];
}

int main() {

    cin.tie(0);
    ios_base::sync_with_stdio(false);
    C[0][0] = 1;
    // usa 
    for (int n = 1; n <= maxn; ++n) {
        C[n][0] = C[n][n] = 1;
        for (int k = 1; k < n; ++k)
            C[n][k] = C[n - 1][k - 1] + C[n - 1][k];
    }


}

