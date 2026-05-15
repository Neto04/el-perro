#include <bits/stdc++.h>
using namespace std;
#define forr(i,a,b) for(int i=a; i<b; i++)


#define EPS 1e-9
struct pt {  // for 3D add z coordinate
    // los puntos tienen coordenadas double
	double x,y;
	pt(double x, double y):x(x),y(y){}
	pt(){}
    // retorna la norma del punto ^ 2
	double norm2(){return *this**this;}
    // retorna la norma con la raiz
	double norm(){return sqrt(norm2());}
    // retorna si los puntos pretty much son iguales
	bool operator==(pt p){return abs(x-p.x)<=EPS&&abs(y-p.y)<=EPS;}
    // suma de puntos
	pt operator+(pt p){return pt(x+p.x,y+p.y);}
    // resta puntos
	pt operator-(pt p){return pt(x-p.x,y-p.y);}
    // producto escalar
	pt operator*(double t){return pt(x*t,y*t);}
    // dividir por escalar
	pt operator/(double t){return pt(x/t,y/t);}
    // producto punto
	double operator*(pt p){return x*p.x+y*p.y;}
//	pt operator^(pt p){ // only for 3D
//		return pt(y*p.z-z*p.y,z*p.x-x*p.z,x*p.y-y*p.x);}
    // me tira el ángulo entre usted y el punto p
    // como cos(cita) = a*b/(||a||*||b||)
    // el mae hace arccos a ambos lados para sacar cita
	double angle(pt p){ // redefine acos for values out of range
		return acos(*this*p/(norm()*p.norm()));}
    // el vector unitario en la misma dirección que usted
	pt unit(){return *this/norm();}
    // producto cruz
    // >0 si p a su izq
    // <0 si p a su der
    // ==0 si p y ud colineales
	double operator%(pt p){return x*p.y-y*p.x;}
	// 2D from now on

    // moralmente es como ordenar un pair
	bool operator<(pt p)const{ // for convex hull
		return x<p.x-EPS||(abs(x-p.x)<=EPS&&y<p.y-EPS);}
    // me dice si está a la izq de la línea (DIRIGIDA) pqs
	bool left(pt p, pt q){
		return (q-p)%(*this-p)>EPS;}
    // rota con respecto a un punto
	pt rot(pt r){return pt(*this%r,*this*r);}
    // rota con respecto a un ángulo (EN RADIANES)
	pt rot(double a){return rot(pt(sin(a),cos(a)));}
};
pt ccw90(1,0);
pt cw90(-1,0);








// CCW order
// Includes collinear points (change sign of EPS in left to exclude)
vector<pt> chull(vector<pt> p){
	if(p.size()<3)return p;
	vector<pt> r;
	sort(p.begin(),p.end()); // first x, then y
	forr(i,0,p.size()){ // lower hull
		while(r.size()>=2&&r.back().left(r[r.size()-2],p[i]))r.pop_back();
		r.push_back(p[i]);
	}
	r.pop_back();
	int k=r.size();
	for(int i=p.size()-1;i>=0;--i){ // upper hull
		while(r.size()>=k+2&&r.back().left(r[r.size()-2],p[i]))r.pop_back();
		r.push_back(p[i]);
	}
	r.pop_back();
	return r;
}