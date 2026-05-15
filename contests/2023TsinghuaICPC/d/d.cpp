#include<bits/stdc++.h>
#include <unordered_map>
using namespace std;
#define int long long int
const int INF = 4e18;
typedef vector<int> vi;
typedef vector<vi> vii;
typedef vector<bool> vb;
typedef vector<vb> vbb;
typedef long double ld;
typedef vector<ld> vd;
typedef vector<vd> vdd;
typedef vector<string> vs;
#define fastio() ios_base::sync_with_stdio(false) ; cin.tie(NULL) ; cout.tie(NULL);
//Fallarian si uso un bitmask que no quepa en un int, por el 1
const double EPS = 1e-15;
#define forn(i, n) for(int i=0; i<n; ++i)
#define sortvi(ar) sort(ar.begin(), ar.end())
#define revsortvi(ar) sort(ar.rbegin(), ar.rend())
#define B_S(v,val) binary_search(v.begin(), v.end(), val)
#define L_B(v,val) lower_bound(v.begin(), v.end(), val) - v.begin()
#define U_B(v,val) upper_bound(v.begin(), v.end(), val) - v.begin()
#define pb push_back
#define Yes cout<<"Yes"<<"\n"
#define No cout<<"No"<<"\n"
typedef priority_queue<int> heapi;
typedef pair<int, int> ii;
typedef vector<ii> vpi;
typedef vector<vpi> vvpi;
#define LSOne(S) ((S) & -(S))
typedef tuple<ld, ld, int> ddi;
const int mod = 1e9 + 7;
#define fs first
#define sd second
#define ce(a) cout << (a) << ' '
#define cln(a) cout << (a) << endl
#define cln_sp(p, a) cout<<fixed<<setprecision(p)<<a<<'\n'
#define ce_sp(p, a) cout<<fixed<<setprecision(p)<<a<<' '
#define ln cout<<'\n'
#define out void(cln("no"))


bool tester(vi& a) {
	int val1 = 0;
	int n = a.size();
	int val2 = a[0] * a.back();
	for (int i = 0; i < n; i += 2) val1 += a[i] * a[i + 1];
	for (int i = 1; i < n; i += 2) val2 *= (a[i] + a[i + 1]);
	if (val1 == val2) {
		//cln("Todo bien");
		return 1;
	}
	cln("Vayase a la mierda");
	return 0;
}

vi tres(int n) {
	assert(n % 4 == 3);

	n >>= 1;
	vi a(n);
	forn(i, n << 1) a[i] = 1 + i & 1;
	for (int i = n << 1; i < n; i++) a[i] = 1;
	return a;
}

void solve() {
	int n; cin >> n;
	n <<= 1;
	vi a(n);
	for (int i = 1; i < n; i += 2) a[i] = 2;
	for (int i = 2; i < n; i += 2) a[i] = -1;
	a.back() = 0;
	int x = 0;
	for (int i = 0; i < n; i += 2) x += a[i] * a[i + 1];
	a.back() = 1;
	a[0] = 1 - x;
	for (auto c : a) ce(c);
	ln;
	//assert(tester(a));
}


int32_t main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int tC; cin >> tC;

	while (tC--) {
		solve();
	}
}