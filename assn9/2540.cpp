#include <iostream>
#include <vector>
#include <string>
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

double area(vector<Point> &poly) {
    double ans = 0;
    for (int i = 2; i < poly.size(); i++)
        ans += cross(poly[0], poly[i-1], poly[i]) / 2;
    return ans;
}

int main() {
    Point curr(0, 0), next;
    vector<Point> poly;
    poly.push_back(Point(0, 0));
    poly.push_back(Point(10, 0));
    poly.push_back(Point(10, 10));
    poly.push_back(Point(0, 10));
    while(!cin.eof()) {
        string verdict;
        cin >> next.x >> next.y >> verdict >> ws;
        if (verdict == "Same") poly.clear();
        Point a((next.x + curr.x) / 2, (next.y + curr.y) / 2),
            b(a.x + curr.y - next.y, a.y + next.x - curr.x);
        if (verdict == "Hotter") poly = hp_cut(poly, a, b);
        else poly = hp_cut(poly, b, a);
        printf("%.2lf\n", area(poly));
        curr = next;
    }
}