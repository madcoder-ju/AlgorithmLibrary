#include <bits/stdc++.h>

using namespace std;

#define P point

using D = double;

const D EPS = 1e-8, PI = acos(-1.0), INF = 1e20;

int compare(D x) {  return fabs(x) < EPS ? 0 : x > EPS ? 1 : -1; }
D square(D x) { return x * x; }
D cube(D x) { return x * x * x; }
D myCeil(D x) { return floor(x * 1000 + 0.5) / 1000; }
D myAcos(D x) { if( x < -1.0 ) return -PI; if( x > 1.0 ) return 0; return acos(x);}
D mySqrt(D x) { if( x < 0.0 ) return 0; return sqrt(x); }

struct point {
    D x, y;
    
    void scan() { cin >> x >> y; }
    
    point() { x = 0; y = 0; }
    point(D p, D q) { x = p; y = q; }

    point operator + (point p) { return point(p.x + x, p.y + y); }
    point operator - (point p) { return point(x - p.x, y - p.y); }
    point operator * (D v) { return point(x * v, y * v); }
    point operator / (D v) { return point(x / v, y / v); }
    bool operator < (point p) const { return !compare(x - p.x) ? y < p.y : x < p.x; }
    bool operator == (point p) { return (!compare(x - p.x) && !compare(y - p.y)); }

    point rotateLeft() { return point(-y, x); }
    point rotateRight() { return point(y, -x); }
};


D det(P p, P q) { return p.x * q.y - p.y * q.x; }
D dot(P p, point q) { return p.x * q.x + p.y * q.y; }
D len2(P a) { return a.x * a.x + a.y * a.y; }
int orient(P a, P b, P c) { int p=det(b-a, c-a);return (p==0 ? 0:(p > 0 ? 1 : -1));}
D distance(P p, P q) { return hypot( p.x - q.x, p.y - q.y ); }
D distancePointLine(P a, P b, P p) {return abs(det(b - a, p - a))/distance(a, b); }
D triangleArea(D a, D b, D c) {D s = (a+b+c)/2.0; return sqrt(s*(s-a)*(s-b)*(s-c));}
D angle(D a, D b, D c) { return acos((a * a + c * c - b * b) / (2.0 * a * c)); }
point unit(P a) { D l = mySqrt(len2(a)); a.x /= l; a.y /= l; return a; }
D vecAngle(P a, P b) { return myAcos(dot( unit( a ), unit( b ))); }


int main() {
	return 0;
}
