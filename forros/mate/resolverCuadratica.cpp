#include <bits/stdc++.h>
#define ll long long
using namespace std;
// retorna # soluciones + un pair en el que vienen en ningún orden en particular
int quadRoots(double a, double b, double c, pair<double,double> &out) {
    assert(a != 0);
    double disc = b*b - 4*a*c;
    if (disc < 0) return 0;
    double sum = (b >= 0) ? -b-sqrt(disc) : -b+sqrt(disc);
    out = {sum/(2*a), sum == 0 ? 0 : (2*c)/sum};
    return 1 + (disc > 0);
}