#include <bits/stdc++.h>
#define ll long long
#define debug 0
#define ifd if(debug)
using namespace std; 

int gcd (int a, int b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}