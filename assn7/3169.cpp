#include <cstdio>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, w;
    Edge() {}
    Edge(int u, int v, int w): u(u), v(v), w(w) {}
};

Edge edge[21000];
int n, dist[1000];
const int INF = 2000000000;

int main() {
    int ml, md, u, v, w;
    scanf("%d %d %d", &n, &ml, &md);
    for(int i = 0; i < ml; i++) {
        scanf("%d %d %d", &u, &v, &w);
        edge[i] = Edge(u-1, v-1, w);
    }
    for(int i = ml; i < ml + md; i++) {
        scanf("%d %d %d", &u, &v, &w);
        edge[i] = Edge(v-1, u-1, -w);
    }
    for(int i = 0; i < n - 1; i++) {
        edge[ml + md + i] = Edge(i+1, i, 0);
    }
    int m = ml + md + n - 1;
    fill(dist, dist + n, INF);
    dist[0] = 0;
    bool update;
    for (int t = 0; t < n; t++) {
        update = false;
        for (int i = 0; i < m; i++) {
            int u = edge[i].u, v = edge[i].v, w = edge[i].w;
            if (dist[v] > dist[u] + w) {
                update = true;
                dist[v] = dist[u] + w;
            }
        }
        if(!update) break;
    }
    if (update) printf("-1\n");
    else if (dist[n-1] > 1100000000) printf("-2\n");
    else printf("%d\n", dist[n-1]);
}