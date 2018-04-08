#include <cstdio>
#include <algorithm>
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

Point intersection(Point a, Point b, Point c, Point d) {
    double x1 = cross(a, b, c), x2 = cross(a, b, d);
    return Point(
        (c.x * x2 - d.x * x1) / (x2 - x1),
        (c.y * x2 - d.y * x1) / (x2 - x1)
    );
}

int n;
Point a[32], b[32], c[32], d[32], x[32][32];

int main() {
    int n;
    scanf("%d", &n);
    while (n > 0) {
        a[0] = Point(0, 0);
        a[n+1] = Point(1, 0);
        for(int i = 1; i <= n; i++){
            a[i].y = 0;
            scanf("%lf", &a[i].x);
        }
        b[0] = Point(0, 1);
        b[n+1] = Point(1, 1);
        for(int i = 1; i <= n; i++){
            b[i].y = 1;
            scanf("%lf", &b[i].x);
        }
        c[0] = Point(0, 0);
        c[n+1] = Point(0, 1);
        for(int i = 1; i <= n; i++){
            c[i].x = 0;
            scanf("%lf", &c[i].y);
        }
        d[0] = Point(1, 0);
        d[n+1] = Point(1, 1);
        for(int i = 1; i <= n; i++){
            d[i].x = 1;
            scanf("%lf", &d[i].y);
        }
        double ans = 0;
        for(int i = 0; i < n+2; i++)
            for(int j = 0; j < n+2; j++) {
                x[i][j] = intersection(c[i], d[i], a[j], b[j]);
                if (i > 0 && j > 0) {
                    double area = (cross(x[i][j], x[i][j-1], x[i-1][j-1]) + cross(x[i][j], x[i-1][j-1], x[i-1][j])) / 2;
                    ans = max(ans, area);
                }
            }
        printf("%lf\n", ans);
        scanf("%d", &n);
    }
}