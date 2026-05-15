#define RB(x) ((x) < n ? r[x] : 0)


void csort(vector<int>& sa, vector<int>& r, int k) {
	int n = sa.size();
	// f al inicio es la frecuencia de cada rank
	vector<int> f(max(255, n)), t(n);
	// para cada maecito, la freq de su rank ++
	forn(i, n) ++f[RB(i+k)];
	int sum = 0;
	// ok, ahora f va a ser: la gente con freq i, a partir de dónde empiezo a ponerlos?
	// esto es para que sepa que los maes con freq i, se ponen en la pos 
	// sum = suma(gente con freq<i)
	forn(i, max(255, n)) f[i] = (sum += f[i]) - f[i];
	// para cada maecito, temp en la posicion de f de su mae, = sa[i]
	// vea que esto es stable_sort vdd
	forn(i, n) t[f[RB(sa[i]+k)]++] = sa[i];
	sa = t;
}
vector<int> compute_sa(string& s){ // O(n*log2(n))
	int n = s.size() + 1, rank;
	vector<int> sa(n), r(n), t(n);
	// me llena sa con 0, 1, 2, ..., n
	iota(sa.begin(), sa.end(), 0);
	forn(i, n) r[i] = s[i];
	for (int k = 1; k < n; k *= 2) {
		// la idea acá es haga sort por 2nd half, luego stable_sort por first half
		csort(sa, r, k), csort(sa, r, 0);
		t[sa[0]] = rank = 0;
		forr(i, 1, n) {
			if(r[sa[i]] != r[sa[i-1]] || RB(sa[i]+k) != RB(sa[i-1]+k)) ++rank;
			t[sa[i]] = rank;
		}
		r = t;
		if (r[sa[n-1]] == n-1) break;
	}
	return sa; // sa[i] = i-th suffix of s in lexicographical order
}

vector<int> compute_lcp(string& s, vector<int>& sa){
	int n = s.size() + 1, L = 0;
	// lcp = lcp
	// plcp = lcp con posición (el mae i en el string, cuál es su lcp con el mae anterior en el suffA)
	// phi = cuál es el sufijo anterior en el suffA
	vector<int> lcp(n), plcp(n), phi(n);
	// el sA en 0 no tiene un anterior
	phi[sa[0]] = -1;
	// para cada maesito, guarde quién es su anterior
	forr(i, 1, n) phi[sa[i]] = sa[i-1];
	
	forn(i,n) {
		// si usted no tiene anterior, su plcp es 0 vdd
		if (phi[i] < 0) { plcp[i] = 0; continue; }
		// vea a ver cuántas letras suyas son iguales que las del anterior
		while(s[i+L] == s[phi[i]+L]) ++L;
		// actualice su plcp vdd
		plcp[i] = L;
		// para el siguiente mae L-1 vdd porque usted le quita la primera letra
		L = max(L - 1, 0);
	}


	// ahora saquemos el lcp 
	forn(i, n) lcp[i] = plcp[sa[i]];
	return lcp; // lcp[i] = longest common prefix between sa[i-1] and sa[i]
}
