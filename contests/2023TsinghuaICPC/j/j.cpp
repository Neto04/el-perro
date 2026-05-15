#include<bits/stdc++.h>
#define forr(i, a, b) for(int i=a; i<b; i++)
#define forn(i,n) forr(i, 0, n)
#define ll long long
#define ii pair<int, int>
#define debug 1
#define ifd if(debug)
using namespace std;

int n;
int parejas;
// pareja la primer pareja, sueltos el primer par de sueltos
ii pareja = { -1,-1 }, sueltos = { -1,-1 };
int ans = -1;

bool unoDos, nUno;

void leerPareja(int u, int v) {
	cout << "? " << u << " " << v << endl;
	cin >> ans;
	if (ans == 1) {
		if (u == 1 and v == 2) unoDos = true;
		if (u == n and v == 1) nUno = true;
		parejas++;
		if (pareja.first == -1) pareja = { u,v };
	}
	else {
		if (sueltos.first == -1) {
			/*
			Si n es impar, no agarro el nodo 1 como suelto para evitar tener
			1 en la primera pareja y en los sueltos al mismo tiempo (en caso
			de que la primera pareja fuera (n,1))
			*/
			if (n % 2) {
				if (u > 1) sueltos = { u,v };
			}
			else {
				sueltos = { u,v };
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tC; cin >> tC;
	while (tC--) {
		cin >> n;
		parejas = 0;
		pareja = { -1,-1 }, sueltos = { -1,-1 };
		ans = -1;
		unoDos = nUno = false;

		// Hago parejas con los nodos
		for (int v = 1; v <= n; v += 2) {
			if (v == n) {
				// Si n es impar, la ultima pareja es (n, 1)
				leerPareja(v, 1);
			}
			else {
				leerPareja(v, v+1);
			}
		}

		if (n % 2) {
			// Si n es impar:
			// Si no hay parejas o hay mas de dos parejas, entonces es un palo
			if ((parejas == 0) or (parejas > 2)) {
				cout << "! 1" << endl;
				continue;
			}
			// Si hay exactamente dos parejas y no son0 1-2, n-1, entonces es un palo
			if ((parejas == 2) and (!unoDos or !nUno)) {
				cout << "! 1" << endl;
				continue;
			}

			if ((parejas == 2) and unoDos and nUno) {
				cout << "? 3 1" << endl;
				cin >> ans;
				if (ans == 1) {
					cout << "! 2" << endl;
				}
				else {
					cout << "! 1" << endl;
				}
				continue;
			}
		}
		else {			
			// Si n es par: si no hay parejas o hay mas de una pareja, entonces es un palo
			if ((parejas == 0) or (parejas > 1)) {
				cout << "! 1" << endl;
				continue;
			}
		}

		/*
		Si hay exactamente una pareja, tengo
		u --- v
		a     b
		Intento pegar a,b a u,v en 3 queries
		*/
		int u = pareja.first, v = pareja.second;
		int a = sueltos.first, b = sueltos.second;
		

		cout << "? " << a << " " << u << endl;
		cin >> ans;
		if (ans == 1) {
			cout << "? " << b << " " << u << endl;
			cin >> ans;
			if (ans == 1) {
				cout << "! 2" << endl;
			}
			else {
				cout << "! 1" << endl;
			}
		}
		else {
			cout << "? " << a << " " << v << endl;
			cin >> ans;
			if (ans == 1) {
				cout << "? " << b << " " << v << endl;
				cin >> ans;
				if (ans == 1) {
					cout << "! 2" << endl;
				}
				else {
					cout << "! 1" << endl;
				}
			}
			else {
				cout << "! 1" << endl;
			}
		}
	}

	return 0;
}