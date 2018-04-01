#include <cstdio>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>
using namespace std;

const int INF = 1000000000;

struct Edge {
    int v, w;
    Edge() {}
    Edge(int v, int w): v(v), w(w) {}
};

struct Entry {
    int u, d;
    Entry() {}
    Entry(int u, int d): u(u), d(d) {}
    bool operator<(const Entry &other) const {
        return d > other.d;
    }
};

int n, m, ds[5000], dt[5000];
vector<Edge> edge[5000];

void dijkstra(int src, int *dist) {
    bool fixed[5000];
    priority_queue<Entry> pq;
    fill(dist, dist + n, INF);
    fill(fixed, fixed + n, false);
    dist[src] = 0;
    pq.push(Entry(src, 0));
    while (!pq.empty()) {
        int u = pq.top().u;
        pq.pop();
        if (fixed[u]) continue;
        fixed[u] = true;
        for (int i = 0; i < edge[u].size(); i++) {
            int v = edge[u][i].v, w = edge[u][i].w;
            if (!fixed[v] && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push(Entry(v, dist[v]));
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        edge[i] = vector<Edge>();
        edge[i].reserve(233);
    }
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        edge[u-1].push_back(Edge(v-1, w));
        edge[v-1].push_back(Edge(u-1, w));
    }
    dijkstra(0, ds);
    dijkstra(n-1, dt);
    int first = 2100000000, second = 2100000000;
    for (int u = 0; u < n; u++)
        for (int i = 0; i < edge[u].size(); i++) {
            int v = edge[u][i].v, w = edge[u][i].w, len = ds[u] + dt[v] + w;
            if (len < first) {
                second = first;
                first = len;
            }
            else if (len > first && len < second) second = len;
        }
    printf("%d\n", second);
}