#include <bits/stdc++.h> 
#define ll long long
using namespace std;

// y = mx + n
// OJO QUE ESTO ES PARA MAXIMIZAR, insertar -m, -n para minimo, sacar -query(x)

// esta vara es para saber si está inserting(0) o querying (1) 
bool Q;
// usted va a guardar lineas que tienen la forma kx+m
struct Line {
    // k la pendiente, m la intersección, p el último pto donde la vara es óptima
    mutable ll k, m, p;
    // si está inserting, los quiero sorted by slope, 
    // si es querying los quiero sorted by punto donde son óptimos
    // en ambos casos, sort de forma cresciente
    bool operator < (const Line &o) const {
        return Q ? p < o.p : k < o.k;
    }
} ;

typedef struct LineContainer : multiset<Line> {
    const ll inf = LLONG_MAX;
    // lol, esto es solo para asegurarse de que haga la parte entera bien y no trollee
    ll div(ll a, ll b) {
        return a / b - ((a ^ b) < 0 && a % b);
    }
    // esto es para encontrar intersección de línea x con línea y
    // actualiza el p de x accordingly 
    // me retorna si x deja de ser useful después de que y deja de ser useful (en cuyo caso, quite y)
    bool isect(iterator x, iterator y) {
        // mae si el otro está al final, diga que usted es infinitamente (a la derecha) útil
        if(y == end()) {
            x->p = inf;
            return false;
        }
        // si tienen la misma pendiente, quédese el que tenga máx m, al otro le pone 
        if(x->k == y->k) x->p = x->m > y->m ? inf : -inf;
        // si no tienen la misma pendiente: x deja de ser útil en la intersección
        else x->p = div(y->m - x->m, x->k - y->k);
        // retorna si x deja de ser useful después de que y deja de ser useful
        return x->p >= y->p;
    }
    // 
    void add(ll k, ll m) {
        // ok, vamos a decir que y es la línea que acabamos de meter, 
        // x la anterior a esa,
        // z la siguiente
        auto z = insert({k, m, 0}), y = z++, x = y;
        // mientras y sirva más que la sig, rip la sig
        while(isect(y, z)) z = erase(z);
        // si la línea anterior la hace a usted useless, rip usted
        if(x != begin() && isect(--x, y)) isect(x, y = erase(y));
        // ehhh solo quite las previous líneas que ahora son useless
        while((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }

    // para encontrar el óptimo de este x
    ll query(ll x) {
        assert(!empty());
        // alchile este mame de cambiar q no tiene sentido, pero confíe
        Q = 1;
        auto l = *lower_bound({0, 0, x});
        Q = 0;
        // se lo retorna evaluado
        return l.k * x + l.m;
    }
} CH;








