#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const float INF = 1e10;

int main() {
    int n;
    scanf("%d", &n);
    while (n >= 0) {
        float x[20], y[20][4], graph[80][80];
        x[0] = 0;
        x[n + 1] = 10;
        for (int j = 0; j < 4; j++) {
            y[0][j] = 5;
            y[n + 1][j] = 5;
        }
        int n_node = (n + 2) * 4;
        for (int i = 0; i < n_node; i++)
            for (int j = 0; j < n_node; j++)
                graph[i][j] = INF;
        for (int i = 1; i < n + 2; i++) {
            if (i <= n) {
                scanf("%f", &x[i]);
                for (int j = 0; j < 4; j++) scanf("%f", &y[i][j]);
            }
            for (int j = 0; j < 4; j++) {
                float x0 = x[i], y0 = y[i][j];
                int idx0 = i * 4 + j;
                for (int i1 = 0; i1 < i; i1++)
                    for (int j1 = 0; j1 < 4; j1++) {
                        float x1 = x[i1], y1 = y[i1][j1];
                        int idx1 = i1 * 4 + j1;
                        bool ok = true;
                        for (int k = i1 + 1; k < i; k++) {
                            float x2 = x[k], y2 = (y0 * (x2 - x1) + y1 * (x0 - x2)) / (x0 - x1);
                            if (y2 < y[k][0] || y2 > y[k][3] || (y2 > y[k][1] && y2 < y[k][2])) {
                                ok = false;
                                break;
                            }
                        }
                        if (ok) graph[idx1][idx0] = sqrt((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1));
                    }
            }
        }
        float dist[80];
        bool fixed[80];
        fill(dist, dist + n_node, INF);
        fill(fixed, fixed + n_node, false);
        dist[0] = 0.0;
        for (int i = 0; i < n_node; i++) {
            float dmin = INF;
            int u = -1;
            for (int j = 0; j < n_node; j++)
                if (!fixed[j] && dist[j] < dmin) {
                    dmin = dist[j];
                    u = j;
                }
            if (u == -1) break;
            fixed[u] = true;
            for (int v = 0; v < n_node; v++)
                if (!fixed[v]) dist[v] = min(dist[v], dist[u] + graph[u][v]);
        }
        printf("%.2f\n", dist[n_node-1]);
        scanf("%d", &n);
    }
}