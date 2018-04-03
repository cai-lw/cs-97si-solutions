#include <cstdio>
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

int n, m, xl, xh, yl, yh, cnt[5001];
Point pl[5001], ph[5001];

int main() {
    scanf("%d", &n);
    while (n > 0) {
        scanf("%d %d %d %d %d", &m, &xl, &yh, &xh, &yl);
        for (int i = 1; i <= n; i++) {
            pl[i].y = yl;
            ph[i].y = yh;
            scanf("%d %d", &ph[i].x, &pl[i].x);
        }
        fill(cnt, cnt + n + 1, 0);
        for (int i = 0; i < m; i++) {
            Point p;
            scanf("%d %d", &p.x, &p.y);
            int l = 0, r = n + 1;
            while (r - l > 1) {
                int mid = (r + l) / 2;
                if (cross(pl[mid], ph[mid], p) > 0) r = mid;
                else l = mid;
            }
            cnt[l]++;
        }
        for (int i = 0; i <= n; i++)
            printf("%d: %d\n", i, cnt[i]);
        scanf("%d", &n);
        if (n > 0) printf("\n");
    }
}