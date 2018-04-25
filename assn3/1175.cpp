#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 1000000000;

struct Point {
    int x, y;
    Point() {}
    Point(int x, int y): x(x), y(y) {}
    bool operator<(Point &other) {
        return (x < other.x) || (x == other.x && y < other.y);
    }
    bool operator==(Point &other) {
        return x == other.x && y == other.y;
    }
};

typedef vector<Point> Stars;

void normalize(Stars &a) {
    int n = a.size(), xmin = INF, ymin = INF;
    for(int i = 0; i < n; i++) {
        xmin = min(xmin, a[i].x);
        ymin = min(ymin, a[i].y);
    }
    for(int i = 0; i < n; i++) {
        a[i].x -= xmin;
        a[i].y -= ymin;
    }
    sort(a.begin(), a.end());
}

void spin(Stars &a) {
    for(int i = 0; i < a.size(); i++) {
        swap(a[i].x, a[i].y);
        a[i].y = -a[i].y;
    }
    normalize(a);
}

void flip(Stars &a) {
    for(int i = 0; i < a.size(); i++) a[i].y = -a[i].y;
    normalize(a);
}

bool smaller(Stars &a, Stars &b) {
    for(int i = 0; i < a.size(); i++) {
        if(a[i] < b[i]) return true;
        if(b[i] < a[i]) return false;
    }
    return false;
}

bool equal(Stars &a, Stars &b) {
    if (a.size() != b.size()) return false;
    for(int i = 0; i < a.size(); i++) {
        if(!(a[i] == b[i])) return false;
    }
    return true;
}

void min_rep(Stars &a) {
    Stars b(a);
    spin(b);
    for(int i = 0; i < 3; i++) {
        if(smaller(b, a)) a = b;
        spin(b);
    }
    flip(b);
    for(int i = 0; i < 3; i++) {
        if(smaller(b, a)) a = b;
        spin(b);
    }
    if(smaller(b, a)) a = b;
}

int w, h, nc;
char m[101][101];
Stars clusters[26];

void floodfill(int x, int y, char src, char dst, Stars *a) {
    if(a) a->push_back(Point(x, y));
    for(int xx = x-1; xx <= x+1; xx++)
        for(int yy = y-1; yy <= y+1; yy++)
            if(xx >= 0 && xx < h && yy >= 0 && yy < w && m[xx][yy] == src) {
                m[xx][yy] = dst;
                floodfill(xx, yy, src, dst, a);
            }
}

Stars get_cluster(int x, int y) {
    Stars a;
    m[x][y] = '?';
    floodfill(x, y, '1', '?', &a);
    normalize(a);
    min_rep(a);
    return a;
}

int main() {
    scanf("%d %d", &w, &h);
    for(int i = 0; i < h; i++) scanf(" %s", m[i]);
    nc = 0;
    for(int i = 0; i < h; i++)
        for(int j = 0; j < w; j++)
            if(m[i][j] == '1') {
                Stars cls = get_cluster(i, j);
                int cls_id = -1;
                for(int k = 0; k < nc; k++)
                    if (equal(cls, clusters[k])) {
                        cls_id = k;
                        break;
                    }
                if(cls_id == -1) {
                    clusters[nc] = cls;
                    cls_id = nc++;
                }
                m[i][j] = 'a' + cls_id;
                floodfill(i, j, '?', 'a' + cls_id, NULL);
            }
    for(int i = 0; i < h; i++) printf("%s\n", m[i]);
}