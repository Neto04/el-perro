#include <bits/stdc++.h>
using namespace std;
#define forn(i, n) for(int i=0; i<n; i++) 
#define dforr(i,a,b) for(int i=int(b)-1;i>=int(a);--i)
#define TYPE int
#define ELEMENTO_NEUTRO -1
#define oper(a, b) a+b




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




int main() {

    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int n, q; cin>>n>>q;
    vector<Mono> a(n);
    forn(i,n)  cin>>a[i].val;
    Segtree st; st.init(a, n);

    while (q--) {
        int op; cin>>op;
        
        if (op==1) {
            int i; Mono v; 
            cin>>i>>v.val;
            st.update(i, v);
        }

        else {
            int l, r; cin>>l>>r;
            cout<<st.query(l, r).val<<"\n";
        }
    }
    
}
