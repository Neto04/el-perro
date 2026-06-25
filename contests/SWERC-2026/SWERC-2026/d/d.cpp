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
    int n; cin>>n;
    vector<int> v(n), freq(1001);
    set<int> s;
    forn(i, n) {
        cin>>v[i];
        s.insert(v[i]);
        freq[v[i]]++;
    }
    int ans =0;
    for(int x:s) {
        if (freq[x]>x) ans+=freq[x]-x;
        else if (freq[x]<x) ans+=freq[x];
    }
    cout<<ans<<"\n";




}
