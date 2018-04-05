#include <cstdio>
#include <list>
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

int linexseg(Point a, Point b, Point c, Point d) {
    double x1 = cross(a, b, c), x2 = cross(a, b, d);
    if (x1 == 0 && x2 == 0) return 0;
    else if (x1 == 0 || x2 == 0) return 1;
    else return ((x1 > 0) ^ (x2 > 0)) ? 1 : -1;
}

bool segxseg(Point a, Point b, Point c, Point d) {
    int r1 = linexseg(a, b, c, d), r2 = linexseg(c, d, a, b);
    if (r1 == 1 && r2 == 1) return true;
    if (r1 == -1 || r2 == -1) return false;
    double d0 = dot(a, b, b), d1 = dot(a, b, c), d2 = dot(a, b, d);
    return !((d1 < 0 && d2 < 0) || (d1 > d0 && d2 > d0));
}

Point p1[100000], p2[100000];
int n;

int main() {
    while (true) {
        scanf("%d", &n);
        if (n == 0) break;
        list<int> ans;
        for (int i = 0; i < n; i++) {
            scanf("%lf %lf %lf %lf", &p1[i].x, &p1[i].y, &p2[i].x, &p2[i].y);
            list<int>::iterator it = ans.begin();
            while(it != ans.end())
                if(segxseg(p1[i], p2[i], p1[*it], p2[*it])) it = ans.erase(it);
                else it++;
            ans.push_back(i);
        }
        printf("Top sticks: %d", ans.front() + 1);
        for(list<int>::iterator it = ++ans.begin(); it != ans.end(); it++)
            printf(", %d", *it + 1);
        printf(".\n");
    }
}