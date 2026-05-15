#include<bits/stdc++.h>
#define forr(i, a, b) for(int i=a; i<b; i++)
#define forn(i,n) forr(i, 0, n)
#define ll long long
#define ii pair<int, int>
#define debug 1
#define ifd if(debug)
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int tC; cin >> tC;
	while (tC--) {
		int n; cin >> n;
		vector<int> v(n);
		forn(i, n) cin >> v[i];
		int start = 0;
		forn(i, n - 1) if (v[i] > v[i + 1]) start = i + 1;
		double ans = 0;
		double left = 0;
		forr(i, start, n) left += v[i];
		// ifd cout << "left = " << left << endl;
		for (int i = start - 1; i >= 0; i--) {
			double curr = v[i] + left;
			curr /= (n -i);
			ans = max(ans, curr);
			left += v[i];
		}

		cout << setprecision(12) << fixed << ans << "\n";


	}







}