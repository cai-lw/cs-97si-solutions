#include <cstdio>
#include <vector>
#include <queue>
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

int n, m, s, t, vertex[1000], dist[1000], cnt0[1000], cnt1[1000];
vector<Edge> edge[1000], rev_edge[1000];
bool fixed[1000];

bool lt_dist(int u, int v) {
    return dist[u] < dist[v];
}

int main() {
    int tc;
    scanf("%d", &tc);
    while (tc--) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n; i++) {
            edge[i] = vector<Edge>();
            edge[i].reserve(233);
            rev_edge[i] = vector<Edge>();
            rev_edge[i].reserve(233);
        }
        for (int i = 0; i < m; i++) {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            edge[u-1].push_back(Edge(v-1, w));
            rev_edge[v-1].push_back(Edge(u-1, w));
        }
        scanf("%d %d", &s, &t);
        s--;
        t--;
        priority_queue<Entry> pq;
        fill(dist, dist + n, INF);
        fill(fixed, fixed + n, false);
        dist[s] = 0;
        pq.push(Entry(s, 0));
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
        fill(cnt0, cnt0 + n, 0);
        fill(cnt1, cnt1 + n, 0);
        cnt0[s] = 1;
        for (int i = 0; i < n; i++) vertex[i] = i;
        sort(vertex, vertex + n, lt_dist);
        for (int i = 0; i < n; i++) {
            int u = vertex[i];
            for (int j = 0; j < rev_edge[u].size(); j++) {
                int v = rev_edge[u][j].v, w = rev_edge[u][j].w;
                if (dist[v] + w == dist[u]) cnt0[u] += cnt0[v];
            }
        }
        for (int i = 0; i < n; i++) {
            int u = vertex[i];
            for (int j = 0; j < rev_edge[u].size(); j++) {
                int v = rev_edge[u][j].v, w = rev_edge[u][j].w;
                if (dist[v] + w == dist[u]) cnt1[u] += cnt1[v];
                if (dist[v] + w == dist[u] + 1) cnt1[u] += cnt0[v];
            }
        }
        printf("%d\n", cnt0[t] + cnt1[t]);
    }
}