#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Edge {
    int v, c, f;
    Edge(int v, int c, int f): v(v), c(c), f(f) {}
};

struct Bfs {
    int u, h;
    Bfs(int u, int h): u(u), h(h) {}
};

class Network {
    vector<vector<int> > edge_ids;
    vector<Edge> edges;
    vector<int> height, ptr;
    bool bfs() {
        int n = edge_ids.size();
        queue<Bfs> q;
        vector<bool> vis(n);
        q.push(Bfs(0, 0));
        vis[0] = true;
        while(!q.empty()) {
            int u = q.front().u, h = q.front().h;
            height[u] = h;
            q.pop();
            for (int i = 0; i < edge_ids[u].size(); i++) {
                Edge &e = edges[edge_ids[u][i]];
                if (e.c > e.f && !vis[e.v]) {
                    q.push(Bfs(e.v, h + 1));
                    vis[e.v] = true;
                }
            }
        }
        return vis[n - 1];
    }
    int dfs(int u, int f) {
        int n = edge_ids.size(), total_flow = 0;
        if (u == n - 1) return f;
        for(;ptr[u] < edge_ids[u].size(); ptr[u]++) {
            Edge &e = edges[edge_ids[u][ptr[u]]], &e_rev = edges[edge_ids[u][ptr[u]] ^ 1];
            if (height[u] + 1 == height[e.v] && e.c > e.f) {
                int flow = dfs(e.v, min(f, e.c - e.f));
                e.f += flow;
                e_rev.f -= flow;
                total_flow += flow;
                f -= flow;
                if (f == 0) break;
            }
        }
        return total_flow;
    }
public:
    Network(int n): edge_ids(n), height(n), ptr(n) {}
    void add_edge(int u, int v, int c) {
        edges.push_back(Edge(v, c, 0));
        edges.push_back(Edge(u, 0, 0));
        edge_ids[u].push_back(edges.size() - 2);
        edge_ids[v].push_back(edges.size() - 1);
    }
    int max_flow() {
        int n = edge_ids.size();
        int ret = 0;
        while (bfs()) {
            fill(ptr.begin(), ptr.end(), 0);
            ret += dfs(0, 2000000000);
        }
        return ret;
    }
};

int main() {
    int n, m;
    while(scanf("%d %d", &m, &n) != EOF) {
        Network net(n);
        for(int i = 0; i < m; i++) {
            int u, v, c;
            scanf("%d %d %d", &u, &v, &c);
            net.add_edge(u - 1, v - 1, c);
        }
        printf("%d\n", net.max_flow());
    }
}