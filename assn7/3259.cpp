#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int v, w;
    Edge() {}
    Edge(int v, int w): v(v), w(w) {}
};

vector<Edge> graph[500];
int dist[500];
const int INF = 1000000000;

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, m, m2;
        scanf("%d %d %d", &n, &m, &m2);
        for (int i = 0; i < n; i++) graph[i] = vector<Edge>();
        int u, v, w;
        for (int i = 0; i < m; i++) {
            scanf("%d %d %d", &u, &v, &w);
            graph[u-1].push_back(Edge(v-1, w));
            graph[v-1].push_back(Edge(u-1, w));
        }
        for (int i = 0; i < m2; i++) {    
            scanf("%d %d %d", &u, &v, &w);
            graph[u-1].push_back(Edge(v-1, -w));
        }
        fill(dist, dist + n, INF);
        dist[0] = 0;
        bool updated;
        for (int i = 0; i < n; i++) {
            updated = false;
            for (int u = 0; u < n; u++)
                for (int j = 0; j < graph[u].size(); j++) {
                    int v = graph[u][j].v, w = graph[u][j].w;
                    if (dist[v] > dist[u] + w) {
                        updated = true;
                        dist[v] = dist[u] + w;
                    }
                }
            if (!updated) break;
        }
        printf(updated ? "YES\n" : "NO\n");
    }
}