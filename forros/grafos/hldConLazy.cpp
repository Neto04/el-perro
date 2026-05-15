#include <bits/stdc++.h>
using namespace std;
#define forr(i, a, b) for (int i=a; i<b; i++)
#define forn(i, n) forr(i, 0, n)

typedef long long ll;
typedef pair<int, int> ii;
#define dforr(i,a,b) for(int i=int(b)-1;i>=int(a);--i)
const int MAXN=100100;
const ll INF=1e9+7;

#define debug 1
#define ifd if (debug)
#define TYPE int
#define ELEMENTO_NEUTRO -1
#define oper(a, b) a+b

/*
NOTAS: 
1. Esto va a ser para RURQ
2. Ojo que si quiere que las aristas tengan pesos en lugar de los nodos, 
ocupa un dfs extra al inicio que le tire profundidad, y luego para una arista de a--b
usted guarda el peso de la arista en el nodo que esté más abajo.
3. ^^si hace eso de arriba^^ tiene que tener cuidado de no incluir el LCA
para evitar eso, en la LINEA MARCADA mete pos[v]+1
*/

// OJO QUE ESTO ES EL SEGTREELAZY DE SUMAAAA
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

// el vector de adj
vector<vector<int>> g;


struct Hld {
	SegtreeLazy st;
	// raiz del heavy path
	int root[MAXN];
    // la posicion en la que aparece en el array
    int pos[MAXN];
    // distancia a la raiz (en #aristas)
    int depth[MAXN];
	// hijo en el heavy path, padre en el rooteo
	int child[MAXN], parent[MAXN];
	int dfs_time;
    // usted está tomando n nodos, con un vector de valores, y tomando como raíz el nodo u
	void init(int u, vector<Mono>& valor, int n) {
        // al inicio nadie tiene hijos
		fill(child, child+n, -1);
        // depth raiz =0
		depth[u] = dfs_time = 0;
        // raiz no tiene papás
		parent[u] = -1;
        // tire los dos dfs
		dfs1(u); dfs2(u, u);
        // preorden va a ser el array que me diga, para cada nodo, cuánto vale, pero en el orden del segment tree
		vector<Mono> preorden(n);
		forn(i,n) preorden[pos[i]] = valor[i];
		st.init(preorden, n);
	}

	void update(int u, int v, Lazy x) {
		// si no están en el mismo heavy-chain, entonces cómase todo el heavy-chain
		for (; root[u] != root[v]; u = parent[root[u]]) {
            // u siempre es el que está en el heavy-chain más bajo
			if (depth[root[u]] < depth[root[v]]) swap(u, v);
            // cómase el heavy chain entero de u
			st.update(pos[root[u]], pos[u]+1, x);
		}
        if (depth[u] < depth[v]) swap(u, v);
        // OJO: si las aristas son las que tienen pesos y no los nodos, esto se hace desde pos[v]+1
        st.update(pos[v], pos[u]+1, x);
	}
    // usted está haciendo un query del camino de u a v
	Mono query(int u, int v) {
		Mono result = Mono::zero();
        // si no están en el mismo heavy-chain, entonces cómase todo el heavy-chain
		for (; root[u] != root[v]; u = parent[root[u]]) {
            // u siempre es el que está en el heavy-chain más bajo
			if (depth[root[u]] < depth[root[v]]) swap(u, v);
            // cómase el heavy chain entero de u
			result = result + st.query(pos[root[u]], pos[u]+1);
		}
		if (depth[u] < depth[v]) swap(u, v);
		// v es el LCA de los u y v iniciales
        // como ahora están en el mismo heavy-chain, solo saque la suma de eso
		// LINEA MARCADA
		result = result + st.query(pos[v], pos[u]+1);
		return result;
	}
    // usted ahorita está en el nodo u
    // actualiza depth, y parente de sus hijos
	int dfs1(int u) {
		int tree_size = 1, child_size;
		int max_child_size = -1;
        // para todos v adj a ud, v != su papá
		for(auto v:g[u])if(v!=parent[u]) {
            // el papá de v es usted, y el depth de v es su depth + 1
			parent[v] = u; depth[v] = depth[u]+1;
            // su propio subtree size += subtree size de v
			tree_size += (child_size = dfs1(v));
            // si es el hijo más gordo, ese es su heavy-hijo
			if (child_size > max_child_size)
				max_child_size = child_size, child[u] = v;
		}
        // di, return su tree size vdd
		return tree_size;
	}
    // usted está en el nodo u que pertenece a una cadena con raíz r
	void dfs2(int u, int r) {
        // guarde la pos en la que va a quedar en el segtree
		pos[u] = dfs_time++; root[u] = r;
        // si tiene un heavy-hijo, vaya a ese primero (ojo que todos sus hijos van a quedar consecutivos en el segtree)
		if (child[u] != -1) dfs2(child[u], r);
        // para los adj que no son su papá ni su heavy-hijo, empiece una heavy cadena en ellos
		for (auto v:g[u]) if (v!=parent[u] && v!=child[u])
			dfs2(v,v);
	}

};







