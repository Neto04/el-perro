// 
#include <bits/stdc++.h>
using namespace std; 
#define forr(i, a, b) for (int i=a; i<b; i++)
#define forn(i, n) forr(i, 0, n)
typedef long long ll;
typedef pair<int, int> ii;

#define debug 0
#define ifd if (debug)

int main() {

    cin.tie(0);
    ios_base::sync_with_stdio(false);

	ll n, q; cin >> n >> q;
	string s; cin >> s;
	vector<ll> v(n);
	forn(i, n) {
		v[i] = s[i] - '0';
	}

	vector<ll> pref4(n, 0), pref8(n, 0);
	if (v[0] == 4) pref4[0] = 1;
	else pref8[0] = 1;
	for (ll i = 1; i < n; i++) {
		pref4[i] = (pref4[i - 1] + (v[i] == 4 ? 1 : 0));
		pref8[i] = (pref8[i - 1] + (v[i] == 8 ? 1 : 0));
	}

	while (q--) {
		ll l, r, x, y; cin >> l >> r >> x >> y;
		l--, r--;
		ll count4, count8;
		if (l > 0) {
			count4 = pref4[r] - pref4[l - 1];
			count8 = pref8[r] - pref8[l - 1];
		}
		else {
			count4 = pref4[r];
			count8 = pref8[r];
		}

		// cuatros es la cantidad de 4s que necesito para llegar sin 8s
		ll cuatros = abs(x) + abs(y);
		// ochos es la cantidad de 8s que me llevan a y
		ll ochos = abs(y);
		// cuatrosOchos es la cantidad de 4s que me llevan a x despues de subir con 8s
		ll cuatrosOchos = max(0LL, abs(x) - abs(y));

		// O sea hay dos formas: cuatros o (ochos + cuatrosOchos)

		ifd{
			cout << "(" << x << "," << y << ")" << endl;
			cout << "Cuatros: " << cuatros << endl;
			cout << "Ochos: " << ochos << endl;
			cout << "Necesito " << cuatros << " cuatro(s) o " << ochos << " ocho(s) y " << cuatrosOchos << " cuatro(s)" << endl;
		}

		if (count4 >= cuatros
			or (count4 >= cuatrosOchos and count8 >= ochos)
			or (count8 <= ochos and count4 >= (cuatrosOchos + 2 * (ochos - count8)))
			or (count4 >= cuatrosOchos + 2 * ochos)
			or (count8 >= cuatros)
			or (count8 >= ochos+cuatrosOchos)
		) {
			cout << "YES\n";
		}
		else cout << "NO\n";
	}

	return 0;
}
