#include <bits/stdc++.h>
#define ll long long
#define forr(i, a, b) for(int i = a; i<b; i++)
#define ifd if(debug)
const int MAXN = 1e6;
using namespace std;
vector <int> prime;
vector<bool> esComp(MAXN);
vector<int> phi(MAXN);

void calcPhi (int n) {
	for (int i = 2; i < n; ++i) {
		if (!esComp[i]) {
			prime.push_back (i);
			phi[i]=i-1;
		}
		for (int j = 0; j < prime.size () && i * prime[j] < n; ++j) {
			esComp[i * prime[j]] = true;
			
			if (i % prime[j] == 0) {
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			}
			else phi[i * prime[j]] = phi[i] * phi[prime[j]];;
		}
	}
}