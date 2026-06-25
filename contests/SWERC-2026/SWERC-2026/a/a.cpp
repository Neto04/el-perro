// 
#include <string>
#include <bits/functexcept.h>
#include <iosfwd>
#include <bits/cxxabi_forced.h>
#include <bits/functional_hash.h>

#pragma push_macro("__SIZEOF_LONG__")
#pragma push_macro("__cplusplus")
#define __SIZEOF_LONG__ __SIZEOF_LONG_LONG__
#define unsigned unsigned long
#define __cplusplus 201102L

#define __builtin_popcountl __builtin_popcountll
#define __builtin_ctzl __builtin_ctzll

#include <bitset>

#pragma pop_macro("__cplusplus")
#pragma pop_macro("__SIZEOF_LONG__")
#undef unsigned
#undef __builtin_popcountl
#undef __builtin_ctzl

#include <bits/stdc++.h>
using namespace std; 
#define forr(i, a, b) for (int i=a; i<b; i++)
#define forn(i, n) forr(i, 0, n)
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;

#define debug 1
#define ifd if (debug)
#define cln(a) cout<<a<<'\n'
#define ln cout<<'\n'
#define ce(a) cout<<a<<' '




#define dforr(i,a,b) for(int i =(b)-1;i>=int(a);--i)
// Lazy es el update pendiente en un nodo
struct Lazy {
    // lo que sea que hay que update
    ll x;
    // el neutro de esos updates
    static Lazy zero() {return {0};}
    // retorna si esa vara es igual al neutro del lazy
    bool is_zero() { return x == 0; } /// moralmente `*this == Lazy::zero()`
};

// lo que sí hay en cada nodo
struct Mono { 
    // el valor en ese nodo
    ll x;
    // el neutro de ese valor
	static Mono zero() {return {0};}
    // a este mono, métale el x de este lazy d
	void apply_lazy(Lazy d, int l, int r) { x += d.x*(r-l); }
};

// para mezclar dos lazies
Lazy operator+ (Lazy a, Lazy b) { return {a.x + b.x}; }
// para mezclar dos Monos
Mono operator+ (Mono a, Mono b) { return {a.x + b.x}; }


// ahora sí, de a de veritas
struct SegtreeLazy {
    // length de la vara
	int len; 
    // la data que hay en cada nodo
    vector<Mono> data; 
    // los updates pendientes que hay en cada nodo
    vector<Lazy> lazy;
    // dado un vector de Monos, cree la vara
	void init(vector<Mono>& a, int n) { assert(n>0); // O(n+len)
		len=1<<(31-__builtin_clz(2*n-1));
		data.assign(2*len, Mono::zero());
		lazy.assign(2*len, Lazy::zero());
		if (a.size()) forn(i, n) data[i+len] = a[i];
		dforr(i, 1, len) data[i] = data[i*2] + data[i*2+1];
	}
    int ql, qr;
    // propague lo que tenga en el nodo i, sabiendo que responde por el intervalo [l, r)
    void p_(int i, int l, int r) {
        // si el mae no tiene nada, no propague nada
		if (lazy[i].is_zero()) return;
        // si el mae no es hoja, propaguele a sus hijos lo que tenga que propagarles
		if (i < len) {
			lazy[2*i] = lazy[2*i] + lazy[i];
			lazy[2*i+1] = lazy[2*i+1] + lazy[i];
		}
        // actualice este mono con lo que tenga en el lazy
		data[i].apply_lazy(lazy[i], l, r);
        // guarde que ya ese mae no tiene nada que updatear
		lazy[i] = Lazy::zero();
	}
    // en este momento está actualizando el nodo i, que responde de l a r, 
    // sabiendo que el intervalo que le interesa ahorita es [ql, qr)
    void u_(int i, int l, int r, Lazy x) {
        // si la vara es hoja, no haga nada
		if (l == r) return;
        // propague lo que tenga en el nodo i, sabiendo que responde por el intervalo [l, r)
		p_(i,l,r);
        // si el mae está out of range, todo bien vdd
		if (r <= ql || qr <= l) return;
        // si está completamente contenido, entonces solo haga el update en su lazy, y ya
		if (ql <= l && r <= qr) {
			lazy[i] = lazy[i] + x;
			p_(i,l,r);
			return;
		}
        
		int m = (l+r)/2;
        // haga update a la izq y derecha
		u_(i*2,l,m,x); u_(i*2+1,m,r,x);
        // ahora actualice su mae
		data[i] = data[2*i] + data[2*i+1];
	}
    // haga un update de [l, r)
	void update(int l, int r, Lazy x) { ql = l; qr = r; u_(1, 0, len, x); }
	// hace un query estando en el nodo i, que responde por [l, r)
    // sabiendo que usted busca [ql, qr)
	Mono q_(int i, int l, int r) {
        // si el mae está afuera, no haga nada
		if (r <= ql || qr <= l) return Mono::zero();
        // propague por si las mosquis
		p_(i,l,r);
        // si el mae está completamente contenido, entonces 
		if (ql <= l && r <= qr) return data[i];
		int m = (l+r)/2;
        // sino, entonces haga query de izq y der
		return q_(i*2,l,m) + q_(i*2+1,m,r);
	}
	// haga un query de l a r
    Mono query(int l, int r) { ql = l; qr = r; return q_(1, 0, len); }
};


int n, k;
vi vog;

int solve1() {
    int n, k; cin>>n>>k;
    vi vog(n);
    forn(i, n) cin>>vog[i];

    n*=4;
    vector<Mono> v2(n);
    for(auto x:vog) v2[x].x = v2[x].x + 1;

	vector<Mono> voc(n);
	SegtreeLazy st; st.init(v2, n);
	SegtreeLazy ocupo; ocupo.init(voc, n);

	map<int, int> ans;
	map<int, int> o2;
	for (int i = 1; i < n; i++) {
		int x = st.query(i, i+1).x;
		if (x <= k) continue;
		x -= (k + 1);
        st.update(i+1, i+x+1, {1});
		st.update(i+x+1, i+x+2, {k});
		//int o = ans[ocupo.query(i, i + 1).x];
		int o = o2[i];
		//Este ocupo no es igual para todos
		ans[i] = x + 1 + o;
		ocupo.update(i + 1, i + x + 2, { ans[i] });
		o2[i + x + 1] = max(o2[i+x+1], ans[i]);
		//ans = max(ac, ans);
	}
	int a = 0;
	for (auto x : ans) a = max(a, x.second);
	cln(a);
	return a;
}

vi v;
set<ii> update_lento(set<ii>& crit) {
	set<ii> ns;
	for (auto [x, i] : crit) {
		i++;
		x--;
		x += v[i];
		if (x>k) ns.emplace(x, i);
	}
	return ns;
}


int solve_lento() {
	//cin >> n >> k;
	//vi vog(n);
	//forn(i, n) cin >> vog[i];
	n*=4;
    v.assign(n, 0);
	for (auto x : vog) v[x]++;
	set<ii> crit;
	forn(i, n) {
		int x = v[i];
		if (x > k) crit.emplace(x, i);
	}
	int ans = 0;
	while (!crit.empty()) {
		crit = update_lento(crit);
		ans++; 
	}
	return (ans);
}

void test() {
	n = rand() % 10;
	k = (rand() % n) + 1;
	vog.assign(n, 0);
	forn(i, n) vog[i] = (rand() % 2 * n) + 1;
	int mala = solve1();
	int lenta = solve_lento();
	if (mala != lenta) {
		ce(n); cln(k);
		for (auto x : vog) ce(x);
		ln; ln; ln;
		ce(mala); cln(lenta);

	}
}
//ans<=n;


int main() {

    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int TC; cin>>TC; 
    while(TC--) solve1();

    
}



/*


1
8 4
1 1 1 1 1 2 2 2





*/