#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#include <utility>
using namespace std;

#define N 203
const int INF = 1000000000;

class Network {
    int cap[N][N], flow[N][N], height[N], ptr[N];
    int n;
    bool bfs() {
        queue<int> q;
        bool vis[N];
        memset(vis, 0, sizeof(vis));
        q.push(0);
        vis[0] = true;
        height[0] = 0;
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v = 0; v < n; v++) {
                if (cap[u][v] > flow[u][v] && !vis[v]) {
                    q.push(v);
                    height[v] = height[u] + 1;
                    vis[v] = true;
                }
            }
        }
        return vis[n - 1];
    }
    int dfs(int u, int f) {
        int total_flow = 0;
        if (u == n - 1) return f;
        for(;ptr[u] < n; ptr[u]++) {
            int v = ptr[u];
            if (height[u] + 1 == height[v] && cap[u][v] > flow[u][v]) {
                int fl = dfs(v, min(f, cap[u][v] - flow[u][v]));
                flow[u][v] += fl;
                flow[v][u] -= fl;
                total_flow += fl;
                f -= fl;
                if (f == 0) break;
            }
        }
        return total_flow;
    }
public:
    Network(int n): n(n) {
        memset(cap, 0, sizeof(cap));
        memset(flow, 0, sizeof(flow));
    }
    void clear_flow() {
        memset(flow, 0, sizeof(flow));
    }
    void add_edge(int u, int v, int c) {
        cap[u][v] += c;
    }
    void remove_edge(int u, int v) {
        cap[u][v] = 0;
    }
    int max_flow() {
        int ret = 0;
        while (bfs()) {
            memset(ptr, 0, sizeof(ptr));
            ret += dfs(0, INF);
        }
        return ret;
    }
};

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, x[100], y[100], p[100], m[100], penguin = 0;
        double d;
        scanf("%d %lf", &n, &d);
        for (int i = 0; i < n; i++) {
            scanf("%d %d %d %d", &x[i], &y[i], &p[i], &m[i]);
            penguin += p[i];
        }
        int count = 0;
        Network net(n * 2 + 2);
        for (int i = 0; i < n; i++) {
            net.add_edge(0, i + 1, p[i]);
            net.add_edge(i + 1, i + n + 1, m[i]);
            for (int j = 0; j < i; j++) {
                int dx = x[i] - x[j], dy = y[i] - y[j], d2 = dx * dx + dy * dy;
                if (d2 <= d * d) {
                    net.add_edge(i + n + 1, j + 1, INF);
                    net.add_edge(j + n + 1, i + 1, INF);
                }
            }
        }
        for (int i = 0; i < n; i++) {
            net.add_edge(i + 1, n * 2 + 1, INF);
            if (net.max_flow() == penguin) {
                printf(count == 0 ? "%d" : " %d", i);
                count++;
            }
            net.remove_edge(i + 1, n * 2 + 1);
            net.clear_flow();
        }
        printf(count == 0 ? "-1\n" : "\n");
    }
}