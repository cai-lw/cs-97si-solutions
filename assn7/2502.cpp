#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const double V_WALK = 10000.0/60.0;
const double V_SUBWAY = 40000.0/60.0;
const double INF = 1e100;

double mag(double x, double y) {
    return sqrt(x * x + y * y);
}

int main() {
    double graph[202][202], x[202], y[202], sub[202];
    scanf("%lf %lf %lf %lf", &x[0], &y[0], &x[1], &y[1]);
    graph[0][1] = mag(x[1] - x[0], y[1] - y[0]) / V_WALK;
    graph[1][0] = graph[0][1];
    int start = 2, n = 2;
    while (scanf("%lf %lf", &x[n], &y[n]) != EOF) {
        if (x[n] >= 0) {
            sub[n-1] = mag(x[n] - x[n-1], y[n] - y[n-1]) / V_SUBWAY;
            double tot = 0.0;
            for (int i = n-1; i >= 0; i--) {
                if (i >= start) tot += sub[i];
                else tot = INF;
                graph[i][n] = min(tot, mag(x[n] - x[i], y[n] - y[i]) / V_WALK);
                graph[n][i] = graph[i][n];
            }
            n++;
        }
        else start = n;
    }
    double dist[202];
    bool fixed[202];
    fill(dist, dist + n, INF);
    fill(fixed, fixed + n, false);
    dist[0] = 0.0;
    for (int i = 0; i < n; i++) {
        double dmin = INF;
        int u = -1;
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
    printf("%.0lf\n", dist[1]);
}