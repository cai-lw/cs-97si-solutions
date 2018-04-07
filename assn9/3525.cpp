#include <cmath>
#include <cstdio>
#include <vector>
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

vector<Point> hp_cut(vector<Point> &poly, Point a, Point b) {
    int n = poly.size();
    vector<double> x(n);
    for(int i = 0; i < n; i++) x[i] = cross(a, b, poly[i]);
    vector<Point> ret;
    for(int i = 0; i < n; i++) {
        int inext = i == n - 1 ? 0 : i + 1;
        if(x[i] < 0) ret.push_back(poly[i]);
        if((x[i] < 0) ^ (x[inext] < 0)) ret.push_back(Point(
            (poly[i].x * x[inext] - poly[inext].x * x[i]) / (x[inext] - x[i]),
            (poly[i].y * x[inext] - poly[inext].y * x[i]) / (x[inext] - x[i])
        ));
    }
    return ret;
}

int main() {
    while(true) {
        int n;
        scanf("%d", &n);
        if (n == 0) break;
        Point p[100];
        for (int i = 0; i < n; i++) {
            scanf("%lf %lf", &p[i].x, &p[i].y);
        }
        double lo = 0, hi = 5000;
        while (hi - lo > 1e-6) {
            double mid = (lo + hi) / 2;
            vector<Point> poly;
            poly.push_back(Point(-1, -1));
            poly.push_back(Point(10001, -1));
            poly.push_back(Point(10001, 10001));
            poly.push_back(Point(-1, 10001));
            bool ok = true;
            for (int i = 0; i < n; i++) {
                int inext = i == n - 1 ? 0 : i + 1;
                double dx = p[inext].x - p[i].x, dy = p[inext].y - p[i].y,
                    norm = sqrt(dx * dx + dy * dy);
                Point a(p[i].x - dy / norm * mid, p[i].y + dx / norm * mid),
                    b(p[inext].x - dy / norm * mid, p[inext].y + dx / norm * mid);
                poly = hp_cut(poly, b, a);
                if(poly.empty()) {
                    ok = false;
                    break;
                }
            }
            if (ok) lo = mid; else hi = mid;
        }
        printf("%lf\n", (lo + hi) / 2);
    }
}