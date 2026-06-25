// 
#include <bits/stdc++.h>
using namespace std; 
#define forr(i, a, b) for (int i=a; i<b; i++)
#define forn(i, n) forr(i, 0, n)
typedef long long ll;
typedef pair<int, int> ii;

#define debug 1
#define ifd if (debug)

int main() {

    cin.tie(0);
    ios_base::sync_with_stdio(false);

	int tC; cin >> tC;
	while (tC--) {
		int n; cin >> n;
		vector<ll> v(n);
		forn(i, n) cin >> v[i];

		ll k = 0, a = 0, b = 0;
		bool pico = false;
		for (int i = 1; i < n and !pico; i++) {
			a = v[i - 1], b = v[i];
			// Hay cambio de linea
			if (a >= b) {
				pico = true;
				break;
			}
		}

		if (pico) k = a / (b - 1);
		else {
			ll mcd = gcd(a, b);
			k = max(b / mcd, mcd);
		}

		cout << k << "\n";
	}

	return 0;
}
