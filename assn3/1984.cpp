#include <vector>
#include <queue>
#include <set>
#include <utility>
#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

class Ufs {
    vector<int> par, rank;
public:
    Ufs(int n): par(n, -1), rank(n, 0) {}
    int find(int i) {
        if (par[i] == -1) return i;
        par[i] = find(par[i]);
        return par[i];
    }
    void merge(int i, int j) {
        i = find(i);
        j = find(j);
        if (i == j) return;
        if (rank[i] < rank[j]) par[i] = j;
        else {
            par[j] = i;
            if (rank[i] == rank[j]) rank[i]++;
        }
    }
};

struct Edge {
    int v, dx, dy;
    Edge(int v, int dx, int dy): v(v), dx(dx), dy(dy) {}
};

struct Query {
    int u, v, t, i;
    Query() {}
    Query(int u, int v, int t, int i): u(u), v(v), t(t), i(i) {}
    bool operator<(Query &other) {
        return t < other.t;
    }
};

int main() {
    int n, m, k;
    scanf("%d %d", &n, &m);
    vector<vector<Edge> > graph(n);
    vector<pair<int, int> > coord(n), log(m);
    for (int i = 0; i < m; i++) {
        int u, v, l, dx = 0, dy = 0;
        char d;
        scanf("%d %d %d %c", &u, &v, &l, &d);
        switch (d) {
            case 'N': dy = l; break;
            case 'S': dy = -l; break;
            case 'E': dx = l; break;
            case 'W': dx = -l; break;
        }
        graph[u - 1].push_back(Edge(v - 1, dx, dy));
        graph[v - 1].push_back(Edge(u - 1, -dx, -dy));
        log[i] = make_pair(u - 1, v - 1);
    }
    vector<bool> vis(n);
    queue<int> q;
    coord[0] = make_pair(0, 0);
    vis[0] = true;
    q.push(0);
    while(!q.empty()) {
        int u = q.front();
        int x = coord[u].first, y = coord[u].second;
        q.pop();
        for(int i = 0; i < graph[u].size(); i++) {
            Edge &e = graph[u][i];
            if (!vis[e.v]) {
                vis[e.v] = true;
                coord[e.v] = make_pair(x + e.dx, y + e.dy);
                q.push(e.v);
            }
        }
    }
    scanf("%d", &k);
    vector<Query> query(k);
    vector<int> ans(k);
    for(int i = 0; i < k; i++) {
        int u, v, t;
        scanf("%d %d %d", &u, &v, &t);
        query[i] = Query(u - 1, v - 1, t - 1, i);
    }
    sort(query.begin(), query.end());
    int ptr = 0;
    Ufs ufs(n);
    for (int i = 0; i < m; i++) {
        ufs.merge(log[i].first, log[i].second);
        while(ptr < k && query[ptr].t <= i) {
            int u = query[ptr].u, v = query[ptr].v;
            if (ufs.find(u) != ufs.find(v))
                ans[query[ptr].i] = -1;
            else 
                ans[query[ptr].i] = abs(coord[u].first - coord[v].first) + abs(coord[u].second - coord[v].second);
            ptr++;
        }
    }
    for (int i = 0; i < k; i++) printf("%d\n", ans[i]); 
}