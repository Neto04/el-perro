#include <bits/stdc++.h>
#define ll long long
#define forr(i, a, b) for(int i = a; i<b; i++)
#define ifd if(debug)
const int MAXN = 1e6;
using namespace std;
vector <int> prime;
vector<bool> esComp(MAXN);
vector<int> func(MAXN);
vector<int> cnt(MAXN);

void calcFunc (int n) {
	for (int i = 2; i < n; ++i) {
		if (!esComp[i]) {
			prime.push_back (i);
			// func[i] = whatever
            cnt[i]=1;
		}
		for (int j = 0; j < prime.size () && i * prime[j] < n; ++j) {
			esComp[i * prime[j]] = true;
			
			if (i % prime[j] == 0) {
                // f(i*p)  = f(i/p^(cnt[i])) * f(p^(t+1))
				// func[i * prime[j]] = func[i] / cnt[i] * (cnt[i] + 1);
				cnt[i * prime[j]] = cnt[i] + 1;
				break;
			}
			else {
                func[i * prime[j]] = func[i] * func[prime[j]];
				cnt[i * prime[j]] = 1;
            }
		}
	}
}