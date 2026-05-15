#include<bits/stdc++.h>
#define forr(i, a, b) for(int i=a; i<b; i++)
#define forn(i,n) forr(i, 0, n)
#define ll long long
#define ii pair<int, int>
#define debug 1
#define ifd if(debug)
using namespace std;

int n, medio; 
vector<double> v;

bool check(double x) {
	vector<double> v2 = v;
	forn(i, n) v2[i] -= x;
	double ans = v2[medio - 1] + v2[medio] + v2[medio + 1];
	double left = 0, cLeft = 0;
	for (int i = medio - 2; i >= 0; i--) {
		cLeft += v2[i];
		left = max(left, cLeft);
	}

	double right = 0, cRight = 0;
	for (int i = medio + 2 ; i<n; i++) {
		cRight += v2[i];
		right = max(right, cRight);
	}
	ans += left + right;
	return (ans >= 0);

}




double bSearch() {

	// a el max que cumple, b el min que no
	double a = 0.00000000001, b = 1e10;
	forr(i, 1, 100) {
		double c;
		if (b > 2 * a) c = sqrt(a * b);
		else c = (a + b) / 2;
		if (check(c)) a = c;
		else b = c;
	}

	return a;
}




int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int tC; cin >> tC;
	while (tC--) {
		cin >> n;
		v.clear(); v.resize(n);
		forn(i, n) {
			int x; cin >> x;
			v[i] = x;
		}
		medio = 0;
		forn(i, n - 1) if (v[i] > v[i + 1]) medio = i + 1;
		
		cout << setprecision(12) << fixed << bSearch() << "\n";


	}







}