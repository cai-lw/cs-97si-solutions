#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct Point {
    int x, y;
    Point() {}
    Point(int x, int y): x(x), y(y) {}
};

int cross(Point a, Point b, Point c) {
    int ux = a.x - b.x, uy = a.y - b.y,
        vx = a.x - c.x, vy = a.y - c.y;
    return ux * vy - uy * vx;
}

int dist2(Point a, Point b) {
    int ux = a.x - b.x, uy = a.y - b.y;
    return ux * ux + uy * uy;
}

Point p[1000];
int n, t, orig;

bool cmp_angle(int i, int j) {
    int x = cross(p[orig], p[i], p[j]);
    if (x != 0) return x > 0;
    else return dist2(p[orig], p[i]) > dist2(p[orig], p[j]); 
}

vector<int> convex_hull() {
    vector<int> ret;
    orig = 0;
    for(int i = 1; i < n; i++)
        if (p[i].x < p[orig].x || (p[i].x == p[orig].x && p[i].y < p[orig].y))
            orig = i;
    ret.push_back(orig);
    vector<int> order;
    order.reserve(n);
    for(int i = 0; i < n; i++)
        if(i != orig) order.push_back(i);
    sort(order.begin(), order.end(), cmp_angle);
    order.push_back(orig);
    ret.push_back(order[0]);
    int start = 1;
    while (cross(p[ret.back()], p[ret[ret.size() - 2]], p[order[start]]) == 0) {
        ret.push_back(order[start]);
        start++;
    }
    reverse(++ret.begin(), ret.end());
    for(int i = start; i < n; i++) {
        while(cross(p[ret.back()], p[ret[ret.size() - 2]], p[order[i]]) > 0) ret.pop_back();
        ret.push_back(order[i]);
    }
    ret.pop_back();
    return ret;
}

int main() {
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        bool collinear = true;
        for(int i = 0; i < n; i++) {
            scanf("%d %d", &p[i].x, &p[i].y);
            if (i > 1 && cross(p[i], p[i-1], p[i-2]) != 0) collinear = false;
        }
        if (collinear || n < 6) {
            printf("NO\n");
            continue;
        }
        vector<int> hull = convex_hull();
        bool ans = true;
        for(int i = 0; i < hull.size(); i++) {
            int j = (i == hull.size()-1) ? 0 : i+1,
                j1 = (j == hull.size()-1) ? 0 : j+1,
                i1 = (i == 0) ? hull.size()-1 : i-1;
            if (cross(p[hull[i]], p[hull[j]], p[hull[j1]]) != 0 && cross(p[hull[i]], p[hull[j]], p[hull[i1]]) != 0) {
                ans = false;
                break;
            }
        }
        if (ans) printf("YES\n"); else printf("NO\n");
    }
}