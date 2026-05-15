#include <bits/stdc++.h>
#define ll long long
#define forr(i, a, b) for(int i = a; i<b; i++)
#define ifd if(debug)
using namespace std;
const int MAXN = 1e6;
vector <int> prime;
vector<bool> esComp(MAXN);

void sieve (int n) {
	for (int i = 2; i < n; ++i) {
		if (!esComp[i]) prime.push_back (i);
		for (int j = 0; j < prime.size () && i * prime[j] < n; ++j) {
			esComp[i * prime[j]] = true;
			if (i % prime[j] == 0) break;
		}
	}
}