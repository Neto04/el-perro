// la operacion
#define OPER min
// el neutro
#define ZERO INT_MAX
struct SparseTable {
    // el spase table
	vector<vector<int>> st;
    // dado un a
	void init(vector<int>& a, int n) {
        // sea k el min mae tq 2^k >n
		int K = 31-__builtin_clz(2*n);
        // inicialice la vara como corresponde
		st.assign(K, vector<int>(n));
        // min(a[i], a[i]+2^0-1]) = a[i]
		forn(i, n) st[0][i] = a[i];
		forr(k,1,K) forn(i,n-(1<<k)+1)
            // min([i, i+2^k-1]) = min([i, i+2^(k-1) -1] U [i+2^k-1, i+2^k -1])
			st[k][i] = OPER(st[k-1][i], st[k-1][i+(1<<(k-1))]);
	}
    // OJO: cero-indexado y responde [l, r)
	int query(int l, int r) {
		if (r <= l) return ZERO;
		int k = 31-__builtin_clz(r-l);
		return OPER(st[k][l], st[k][r-(1<<k)]);
	}
};
