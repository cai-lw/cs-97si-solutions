#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

float graph[200][200], dist[200];
int x[200], y[200];
bool fixed[200];
const float INF = 1e10;

int main() {
    int n, cas = 0;
    scanf("%d", &n);
    while (n > 0) {
        for (int i = 0; i < n; i++) {
            scanf("%d %d", &x[i], &y[i]);
        }
        for (int i = 0; i < n; i++) {
            graph[i][i] = 0.0;
            for (int j = i + 1; j < n; j++) {
                int dx = x[i] - x[j], dy =y[i] - y[j], d2 = dx * dx + dy * dy;
                graph[i][j] = sqrt(float(d2));
                graph[j][i] = graph[i][j];
            }
        }
        fill(dist, dist + n, INF);
        fill(fixed, fixed + n, false);
        dist[0] = 0.0;
        for (int i = 0; i < n; i++) {
            float dmin = INF;
            int u = -1;
            for (int j = 0; j < n; j++)
                if (!fixed[j] && dist[j] < dmin) {
                    dmin = dist[j];
                    u = j;
                }
            if (u == -1) break;
            fixed[u] = true;
            for (int v = 0; v < n; v++)
                if (!fixed[v]) dist[v] = min(dist[v], max(dist[u], graph[u][v]));
        }
        printf("Scenario #%d\n", ++cas);
        printf("Frog Distance = %.3lf\n", dist[1]);
        scanf("%d", &n);
        if (n > 0) printf("\n");
    }
}