#include <cstdio>
#include <cmath>
using namespace std;

struct Point {
    double x, y;
    Point() {}
    Point(double x, double y): x(x), y(y) {}
};

double cross(Point a, Point b, Point c) {
    double ux = a.x - b.x, uy = a.y - b.y,
        vx = a.x - c.x, vy = a.y - c.y;
    return ux * vy - uy * vx;
}

double dot(Point a, Point b, Point c) {
    double ux = a.x - b.x, uy = a.y - b.y,
        vx = a.x - c.x, vy = a.y - c.y;
    return ux * vx + uy * vy;
}

double dist2(Point a, Point b) {
    return dot(a, b, b);
}

int n;
double r, r2;
Point peg, p[100000];

int main() {
    while(true) {
        scanf("%d", &n);
        if(n < 3) break;
        scanf("%lf %lf %lf", &r, &peg.x, &peg.y);
        r2 = r * r;
        for(int i = 0; i < n; i++) {
            scanf("%lf %lf", &p[i].x, &p[i].y);
        }
        bool l = false, r = false, cl = false, cr = false, intersect = false;
        for(int i = 0; i < n; i++) {
            int prv = (i == 0) ? n - 1 : i - 1,
                nxt = (i == n - 1) ? 0 : i + 1;
            double x = cross(p[i], p[prv], p[nxt]),
                xc = cross(p[i], peg, p[nxt]);
            l = l || x < 0;
            r = r || x > 0;
            cl = cl || xc <= 0;
            cr = cr || xc >= 0;
            if (dist2(peg, p[i]) < r2 || dist2(peg, p[nxt]) < r2) intersect = true;
            else if(dot(p[i], p[nxt], peg) > 0 && dot(p[nxt], p[i], peg) > 0) {
                double h2 = xc * xc / dist2(p[i], p[nxt]);
                if (h2 < r2) intersect = true;
            }
        }
        if(l && r) printf("HOLE IS ILL-FORMED\n");
        else if(intersect || (l && cr) || (r && cl)) printf("PEG WILL NOT FIT\n");
        else printf("PEG WILL FIT\n");
    }
}