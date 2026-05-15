#include <bits/stdc++.h>
using namespace std;

bool circleCircle(pt c1, double r1, pt c2, double r2, pair<pt,pt> &out) {
    double d = abs(c2-c1), co = (d*d + r1*r1 - r2*r2)/(2*d*r1);
    if (abs(co) > 1) return false;
    double alpha = acos(co);
    pt rad = (c2-c1)/d*r1; // vector C1C2 resized to have length d
    out = {c1 + rot(rad, -alpha), c1 + rot(rad, alpha)};
    return true;
}