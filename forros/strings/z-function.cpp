// fumado de Prim Floyd (no tengo el link)
#include <bits/stdc++.h>
#define debug 1
#define ifd if(debug) 
#define forr(i, a, b) for(int i=a; i<b; i++)
#define forn(i, b) forr(i, 0, b)
#define ll long long 
using namespace std;
// usted quiere, dado un string s, un array z que le diga en z[i]
// el max k tq s[i, ..., i+k-1] es prefijo (no puede ser el string completo)
// complejidad: O(n), con n = s.size()
vector<int> zeta(string s) {
  int n = s.size();
  vector<int> z(n);
//   x y y son dos puntos tq s[x...y] es prefijo & y es el más a la der que ha visto
  int x = 0, y = 0;
  for (int i = 1; i < n; i++) {
    // si i+z[i-x]<y, entonces de fijo a usted le toca z[i-x]
    // sino, por ahora diga que es la cantidad de gente que hay en frente suyo (que sería y-i+1)
    z[i] = max(0,min(z[i-x],y-i+1));
    // mientras todavía pueda meter letras, y esas letras sean válidas, métalas
    // actualice de paso x y y
    while (i+z[i] < n && s[z[i]] == s[i+z[i]])
        x = i, y = i+z[i], z[i]++;
  }
  return z;}