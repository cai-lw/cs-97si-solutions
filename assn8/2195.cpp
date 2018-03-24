#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

#define N 203
const int INF = 1000000000;

class Network {
    int cap[N][N], flow[N][N], cost[N][N], height[N];
    int n, pot;
    void floyd() {
        int dist[N][N];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (i == j) dist[i][j] = 0;
                else if (cap[i][j] > flow[i][j]) dist[i][j] = cost[i][j];
                else dist[i][j] = INF;
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        memcpy(height, dist[0], sizeof(height));
    }
    pair<int, int> dijkstra() {
        int dist[N], prev[N], f[N];
        bool fixed[N];
        memset(fixed, false, sizeof(fixed));
        memset(prev, 0, sizeof(prev));
        memset(f, 0, sizeof(f));
        f[0] = INF;
        dist[0] = 0;
        for (int i = 1; i < n; i++) dist[i] = INF;
        for (int _ = 0; _ < n; _++) {
            int min_dist = INF, u = -1;
            for (int i = 0; i < n; i++)
                if (!fixed[i] && dist[i] < min_dist) {
                    min_dist = dist[i];
                    u = i;
                }
            if (min_dist == INF) break;
            fixed[u] = true;
            for (int v = 0; v < n; v++)
                if (u != v && !fixed[v] && cap[u][v] > flow[u][v] && dist[u] + cost[u][v] < dist[v]) {
                    dist[v] = dist[u] + cost[u][v];
                    prev[v] = u;
                    f[v] = min(f[u], cap[u][v] - flow[u][v]);
                }
        }
        if (dist[n - 1] == INF) return make_pair(0, 0);
        int v = n - 1;
        do {
            int u = prev[v];
            flow[u][v] += f[n - 1];
            flow[v][u] -= f[n - 1];
            v = u;
        } while (v > 0);
        memcpy(height, dist, sizeof(height));
        return make_pair(f[n - 1], f[n - 1] * (dist[n - 1] + pot));
    }
    void update_cost() {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cost[i][j] -= height[j] - height[i];
        pot += height[n - 1];
    }
public:
    Network(int n): n(n), pot(0) {
        memset(cap, 0, sizeof(cap));
        memset(flow, 0, sizeof(flow));
        memset(cost, 0, sizeof(flow));
    }
    void add_edge(int u, int v, int c, int w) {
        cap[u][v] = c;
        cost[u][v] = w;
        cost[v][u] = -w;
    }
    pair<int, int> min_cost_max_flow() {
        int max_flow = 0, min_cost = 0;
        floyd();
        update_cost();
        while (true) {
            pair<int, int> res = dijkstra();
            if (res.first == 0) break;
            max_flow += res.first;
            min_cost += res.second;
            update_cost();
        }
        return make_pair(max_flow, min_cost);
    }
};

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    while (n > 0 && m > 0) {
        vector<pair<int, int> > house, man;
        for (int i = 0; i < n; i++) {
            char s[101];
            scanf("%s", s);
            for (int j = 0; j < m; j++) {
                if (s[j] == 'H') house.push_back(make_pair(i, j));
                else if (s[j] == 'm') man.push_back(make_pair(i, j));
            }
        }
        int k = house.size();
        Network net(k * 2 + 2);
        for (int i = 0; i < k; i++) {
            net.add_edge(0, i + 1, 1, 0);
            net.add_edge(i + k + 1, k * 2 + 1, 1, 0);
        }
        for (int i = 0; i < k; i++)
            for (int j = 0; j < k; j++) {
                int dist = abs(man[i].first - house[j].first) + abs(man[i].second - house[j].second);
                net.add_edge(i + 1, j + k + 1, 1, dist);
            }
        printf("%d\n", net.min_cost_max_flow().second);
        scanf("%d %d", &n, &m);
    }
}