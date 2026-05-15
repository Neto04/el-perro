#include <bits/stdc++.h>

using namespace std;

#pragma GCC optimize("Ofast","unroll-loops","omit-frame-poller","inline","03")


typedef long long ll;
// este log sirve hasta 1e6
const int logn = 21; // 2^logn >= n!!!
const int maxn = 1 << logn; // 2^logn >= n!!!

ll Hilbert(int x, int y) {
    ll d = 0;
    for(int s = 1 << (logn - 1); s; s >>= 1) {
        bool rx = x & s, ry = y & s;
        d = d << 2 | rx * 3 ^ static_cast<int>(ry);
        if(!ry) {
            if(rx) {
                x = maxn - x;
                y = maxn - y;
            }
            swap(x, y);
        }
    }
    return d;
}

struct Query {
    // esta vara tiene 4 parámetros: l, r, queryId, y el ordenRandom ese de Hilbert
    int a, b, id;
    ll ord;
    Query(int x = 0, int y = 0, int z = 0) : a(x), b(y), id(z) {
        ord = Hilbert(x, y);
    }
    bool operator < (const Query &a) const {
        return ord < a.ord;
    }
} ;

vector <Query> mo;

int n, q, x, y;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> q;
    // ok, a es el vector original
    vector <int> a(n + 1);
    // la respuesta para cada query
    vector <ll> sol(q);
    // lea a
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    // sea c un
    vector <int> c(*max_element(a.begin(), a.end()) + 1);
    // lea los queries, metiendo cada [l, r]
    for(int i = 1; i <= q; i++) {
        cin >> x >> y;
        mo.push_back(Query(x, y, i));
    }
    // haga el sort raro de mo
    sort(mo.begin(), mo.end());
    // v es su respuesta ahorita
    ll v = 0;
    // defina qué significa add alguien
    auto add = [&](ll z) {
        // TODO: definir qué significa add a un mae
    } ;
    // defina qué significa sacar alguien
    auto del = [&](ll z) {
        // TODO: definir qué significa del a un mae
    };
    // x :=current l, y :=current r
    x = 1, y = 0;
    // 
    for(auto [l, r, p, z] : mo) {
        while(y < r)add(a[++y]);
        while(x > l)add(a[--x]);
        while(y > r)del(a[y--]);
        while(x < l)del(a[x++]);
        sol[p - 1] = v;
    }

    for(auto r : sol)
        cout << r << '\n';

    return 0;
}