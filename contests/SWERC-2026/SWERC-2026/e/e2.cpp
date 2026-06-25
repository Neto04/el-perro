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
		x = abs(x), y = abs(y);
		ll count4, count8;
		if (l > 0) {
			count4 = pref4[r] - pref4[l - 1];
			count8 = pref8[r] - pref8[l - 1];
		}
		else {
			count4 = pref4[r];
			count8 = pref8[r];
		}

		ll mini = min({ x, y, count8 });
		ll target = x + y - 2 * mini;
		if (count4 + count8 - mini >= target) cout << "YES\n";
		else cout<<"NO\n";

	}

	return 0;
}
