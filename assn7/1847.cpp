#include <cstdio>
#include <algorithm>
using namespace std;

int graph[100][100], dist[100];
bool fixed[100];
const int INF = 1000000000;

int main() {
    int n, a, b;
    scanf("%d %d %d", &n, &a, &b);
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) graph[u][v] = INF;
        graph[u][u] = 0;
        int m;
        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            int v;
            scanf("%d", &v);
            graph[u][v-1] = i == 0 ? 0 : 1;
        }
    }
    fill(dist, dist + n, INF);
    fill(fixed, fixed + n, false);
    dist[a-1] = 0;
    for (int i = 0; i < n; i++) {
        int dmin = INF, u = -1;
        for (int j = 0; j < n; j++)
            if (!fixed[j] && dist[j] < dmin) {
                dmin = dist[j];
                u = j;
            }
        if (u == -1) break;
        fixed[u] = true;
        for (int v = 0; v < n; v++)
            if (!fixed[v]) dist[v] = min(dist[v], dist[u] + graph[u][v]);
    }
    int ans = dist[b-1];
    printf("%d\n", ans == INF ? -1 : ans);
}