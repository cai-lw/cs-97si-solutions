#include <cstdio>
#include <algorithm>
using namespace std;

const int INF = 1000000000;

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

int dot(Point a, Point b, Point c) {
    int ux = a.x - b.x, uy = a.y - b.y,
        vx = a.x - c.x, vy = a.y - c.y;
    return ux * vx + uy * vy;
}

int dist2(Point a, Point b) {
    int ux = a.x - b.x, uy = a.y - b.y;
    return ux * ux + uy * uy;
}

int main() {
    int n, t, id[50], path[50];
    bool vis[50];
    Point p[50], curr = Point(INF, INF), prev;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        fill(path, path + n, 0);
        fill(vis, vis + n, false);
        for(int i = 0; i < n; i++) {
            scanf("%d %d %d", &id[i], &p[i].x, &p[i].y);
            if(p[i].y < curr.y || (p[i].y == curr.y && p[i].x < curr.x)) {
                curr = p[i];
                path[0] = i;
                
            }
        }
        
        vis[path[0]] = true;
        prev = curr;
        prev.x = 0;
        for(int i = 1; i < n; i++) {
            int next = -1;
            for(int j = 0; j < n; j++)
                if (vis[j]) continue;
                else if (next == -1) next = j;
                else {
                    int x = cross(curr, p[next], p[j]);
                    if (x < 0 || (x == 0 && dist2(curr, p[j]) < dist2(curr, p[next]))) next = j;
                }
            path[i] = next;
            vis[next] = true;
            prev = curr;
            curr = p[next];
        }
        printf("%d", n);
        for(int i = 0; i < n; i++) printf(" %d", id[path[i]]);
        printf("\n");
    }
}