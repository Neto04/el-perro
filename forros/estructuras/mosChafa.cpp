// el de Teruel es muy violento, entonces aqui hay un mos mío


ll raizQ(ll a) {
    long long x = sqrt(a) + 2;
    while (x * x > a) x--;

    return x;
}

struct mae{
    ll bloque;
    ll r; ll l;
    ll queryId;
};

bool comp(mae m1, mae m2) {
    if (m1.bloque!=m2.bloque) return m1.bloque<m2.bloque;
    else if (m1.r!=m2.r) return m1.r<m2.r;
    else if (m1.l!=m2.l) return m1.l<m2.l;
    return m1.queryId<m2.queryId;
}

int main() {

    cin.tie(0);
    ios_base::sync_with_stdio(false);
    ll n; cin>>n;
    ll sqrt=raizQ(n);

    vector<int> v(n+1);
    forr(i,1, n+1) cin>>v[i];
    int q; cin>>q;
    vector<mae> maes(q);
    forn(i, q) {
        cin>>maes[i].l>>maes[i].r;
        maes[i].bloque=(maes[i].l/sqrt);
        maes[i].queryId=i;
    }
    sort(maes.begin(), maes.end(), comp);
    
    vector<int> ocurrencias(1e6+5);
    vector<ll> ans(q);

    int oldIzqPointer=maes[0].l, oldDerPointer=maes[0].r, oldAns;
    for (int i=oldIzqPointer; i<=maes[0].r; i++) {
        ocurrencias[v[i]]++;
        if (ocurrencias[v[i]]==1) ans[maes[0].queryId]++;
    }

    oldAns=ans[maes[0].queryId];
    int currAns;
    int currIzqPointer, currDerPointer;
    for (int i=1; i<q; i++) {
        currAns=oldAns;
        currIzqPointer=maes[i].l;
        currDerPointer=maes[i].r;
        // si el izqViejo está más a la izq
        while (oldIzqPointer<currIzqPointer) {
            ocurrencias[v[oldIzqPointer]]--;
            if (ocurrencias[v[oldIzqPointer]]==0) currAns--;
            oldIzqPointer++;
        }
        //si el izqViejo está más a la der
        while(oldIzqPointer>currIzqPointer) {
            oldIzqPointer--;
            ocurrencias[v[oldIzqPointer]]++;
            if (ocurrencias[v[oldIzqPointer]]==1) currAns++;
        }

        // si el derViejo está más a la der
        while (oldDerPointer>currDerPointer) {
            ocurrencias[v[oldDerPointer]]--;
            if (ocurrencias[v[oldDerPointer]]==0) currAns--;
            oldDerPointer--;
        }

        // si el derViejo está más a la izq
        while (oldDerPointer<currDerPointer) {
            oldDerPointer++;
            ocurrencias[v[oldDerPointer]]++;
            if (ocurrencias[v[oldDerPointer]]==1) currAns++;
        }

        ans[maes[i].queryId]=currAns;
        oldAns=currAns;
        oldIzqPointer=currIzqPointer;
        oldDerPointer=currDerPointer;
    }

    forn(i, q) cout<<ans[i]<<"\n";
 }