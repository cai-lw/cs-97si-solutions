#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct Event {
    double pos;
    int diff;
    Event() {}
    Event(double pos, int diff): pos(pos), diff(diff) {}
    bool operator<(const Event &other) const {
        return pos < other.pos;
    }
};

int main() {
    while (true) {
        double hl, hr, hy, pl, pr, py, l, r, y;
        scanf("%lf %lf %lf", &hl, &hr, &hy);
        if (hl == 0.0 && hr == 0.0 && hy == 0.0) break;
        scanf("%lf %lf %lf", &pl, &pr, &py);
        int n;
        scanf("%d", &n);
        vector<Event> e;
        e.reserve(n * 2 + 2);
        e.push_back(Event(pl, -1));
        e.push_back(Event(pr, 1));
        for (int i = 0; i < n; i++) {
            scanf("%lf %lf %lf", &l, &r, &y);
            if (y >= hy || y <= py) continue;
            e.push_back(Event(hr + (l - hr) / (hy - y) * (hy - py), 1));
            e.push_back(Event(hl + (r - hl) / (hy - y) * (hy - py), -1));
        }
        sort(e.begin(), e.end());
        double ans = 0.0, pos = -1e10;
        int cnt = 1;
        for (int i = 0; i < e.size(); i++) {
            if (cnt == 0) ans = max(ans, e[i].pos - pos);
            pos = e[i].pos;
            cnt += e[i].diff;
        }
        if (ans < 1e-8) printf("No View\n");
        else printf("%.2lf\n", ans);
    }
}