#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef long long ll;

struct Point {
    ll x, y;
    Point() {}
    Point(ll x, ll y): x(x), y(y) {}
};

Point vtx[100];
ll dp[50][100];
int n;
bool chord[100][100];

ll cross(Point a, Point b, Point c) {
    ll ux = a.x - b.x, uy = a.y - b.y,
      vx = a.x - c.x, vy = a.y - c.y;
    return ux * vy - uy * vx;
}

ll area2(Point a, Point b, Point c) {
    ll x = cross(a, b, c);
    return x > 0 ? x : -x;
}

ll dot(Point a, Point b, Point c) {
    ll ux = a.x - b.x, uy = a.y - b.y,
      vx = a.x - c.x, vy = a.y - c.y;
    return ux * vx + uy * vy;
}

int rayxseg(Point a, Point b, Point c, Point d) {
    ll x1 = cross(a, b, c), x2 = cross(a, d, b);
    if (x1 == 0) return (dot(a, b, c) > 0 || x2 == 0 && dot(a, b, d) > 0) ? 0 : -1;
    if (x2 == 0) return dot(a, b, d) > 0 ? 0 : -1;
    ll x3 = cross(a, d, c);
    return (x1 > 0 && x2 > 0 && x3 > 0) || (x1 < 0 && x2 < 0 && x3 < 0) ? 1 : -1;
}

int linexseg(Point a, Point b, Point c, Point d) {
    ll x1 = cross(a, b, c), x2 = cross(a, b, d);
    if (x1 == 0 && x2 == 0) return 0;
    else if (x1 == 0 || x2 == 0) return 1;
    else return ((x1 > 0) ^ (x2 > 0)) ? 1 : -1;
}

bool segxseg(Point a, Point b, Point c, Point d) {
    ll r1 = linexseg(a, b, c, d), r2 = linexseg(c, d, a, b);
    if (r1 == 1 && r2 == 1) return true;
    if (r1 == -1 || r2 == -1) return false;
    ll d0 = dot(a, b, b), d1 = dot(a, b, c), d2 = dot(a, b, d);
    return !((d1 < 0 && d2 < 0) || (d1 > d0 && d2 > d0));
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            int xx, yy;
            scanf("%d %d", &xx, &yy);
            Point p(xx, yy);
            vtx[i] = p;
            vtx[i + n] = p;
        }
        for (int i = 0; i < n * 2 - 1; i++) chord[i][i+1] = true;
        for (int i = 0; i < n; i++)
            for (int j = i + 2; j < (i == 0 ? n-1 : n); j++) {
                bool ok = true;
                for (int k = 0; k < n; k++) {
                    if (k == (i == 0 ? n-1 : i-1) || k == i || k == j-1 || k == j) continue;
                    if (segxseg(vtx[i], vtx[j], vtx[k], vtx[k+1])) {
                        ok = false;
                        break;
                    }
                }
                if (ok) {
                    while (true) {
                        Point pr(rand() % 20003, rand() % 20003),
                              pc(vtx[i].x + vtx[j].x, vtx[i].y + vtx[j].y);
                        if (pr.x == pc.x && pr.y == pc.y) continue;
                        int cnt = 0;
                        for (int k = 0; k < n; k++) {
                            Point p1(vtx[k].x * 2, vtx[k].y * 2),
                                    p2(vtx[k+1].x * 2, vtx[k+1].y * 2);
                            int r = rayxseg(pc, pr, p1, p2);
                            if (r == 0) {
                                cnt = -1;
                                continue;
                            }
                            if (r == 1) cnt++;
                        }
                        if (cnt == -1) continue;
                        ok = cnt % 2 == 1;
                        break;
                    }
                }
                chord[i][j] = ok;
                chord[j][i + n] = ok;
                chord[i + n][j + n] = ok;
            }
        for (int i = 0; i < n * 2; i++) dp[1][i] = 0;
        for (int i = 2; i < n; i++)
            for (int j = 0; j < n; j++) {
                dp[i][j] = 0x7FFFFFFF;
                for (int k = 1; k < i; k++)
                    if (chord[j][j+k] && chord[j+k][j+i])
                        dp[i][j] = min(dp[i][j], max(area2(vtx[j], vtx[j+k], vtx[j+i]), max(dp[k][j], dp[i-k][j+k])));
            }
        printf("%lld", dp[n-1][0] / 2);
        if (dp[n-1][0] % 2 == 1) printf(".5\n");
        else printf(".0\n");
    }
}