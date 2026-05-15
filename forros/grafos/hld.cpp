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

1. Ojo que esto es para PURQ
2. Ojo que si quiere que las aristas tengan pesos en lugar de los nodos, 
ocupa un dfs extra al inicio que le tire profundidad, y luego para una arista de a--b
usted guarda el peso de la arista en el nodo que esté más abajo.
3. ^^si hace eso de arriba^^ tiene que tener cuidado de no incluir el LCA
para evitar eso, en la LINEA MARCADA mete pos[v]+1

*/

struct Mono {
    
	TYPE val;
    // return elemento neutro
	static Mono zero() { return {ELEMENTO_NEUTRO}; } // neutro de la suma
};
Mono operator+ (Mono a, Mono b) {
	return {oper(a.val, b.val)};
} // asociativo


struct Segtree {
	int len; vector<Mono> data;
    
	void init(vector<Mono>&a, int n) { assert(n>0); // O(n+len)
		// len =  min k tq 2^k>=n
		len=1<<(31-__builtin_clz(2*n-1));
		// y usted mete len*2
		data.assign(len*2, Mono::zero());
        // revise que la vara exista, y en las hojas usted mete a[i]
		if (!a.empty()) forn(i, n) data[i+len] = a[i];
        // ahora, de las hojas patrás retorne la combinación de las dos
		dforr(i, 1, len) data[i] = data[i*2] + data[i*2+1];
	}

    // actualice el mae en i a x
	void update(int i, Mono x) {
        // primero la hoja
		i += len; data[i] = x;
        // luego vaya de abajo a arriba
        while (i /= 2) data[i] = data[i*2] + data[i*2+1];
	}

	int ql, qr;
    // sabiendo que está en el nodo i, revise qué hay en [l, r)
	Mono q_(int i, int l, int r) {
        // si i está completamente disjunto, retorne el nulo
		if (r <= ql || qr <= l) return Mono::zero();
        // si está completamente contenido, retorne ese nodo
		if (ql <= l && r <= qr) return data[i];
		int m = (l+r)/2;
        // retorne la intersección de los dos maes
		return q_(i*2,l,m) + q_(i*2+1,m,r);
	}
    // preguntan por l, r, sepa que va a empezar desde el nodo 1 preguntando por (0, len)
	Mono query(int l, int r) { ql = l; qr = r; return q_(1, 0, len); }
};

// el vector de adj
vector<vector<int>> g;


struct Hld {
	Segtree st;
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

	void update(int u, Mono x) {
		st.update(pos[u], x);
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
		// VVV LINEA MARCADA VVV
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







