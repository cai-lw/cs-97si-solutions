#include <cstdio>
#include <algorithm>
using namespace std;

int dist[100][100];
const int INF = 1000000000;

int main() {
    int n;
    scanf("%d", &n);
    while (n > 0) {
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) dist[u][v] = INF;
            dist[u][u] = 0;
            int m;
            scanf("%d", &m);
            for (int i = 0; i < m; i++) {
                int v, w;
                scanf("%d %d", &v, &w);
                dist[u][v-1] = w;
            }
        }
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        int ansu = -1, anst = INF;
        for (int u = 0; u < n; u++) {
            int maxt = 0;
            for (int v = 0; v < n; v++)
                maxt = max(maxt, dist[u][v]);
            if (maxt < anst) {
                anst = maxt;
                ansu = u;
            }
        }
        if (ansu == -1) printf("disjoint\n");
        else printf("%d %d\n", ansu+1, anst);
        scanf("%d", &n);
    }
}