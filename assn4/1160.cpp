#include <cstdio>
#include <algorithm>
using namespace std;

const int INF = 2147483647;

int main() {
    int dp[300][31], v, p, x[300], xsum[301], ans = INF;
    scanf("%d %d", &v, &p);
    xsum[0] = 0;
    for (int i = 0; i < v; i++) {
        scanf("%d", &x[i]);
        xsum[i + 1] = xsum[i] + x[i];
    }
    for (int i = 0; i < v; i++) {
        dp[i][1] = x[i] * (i + 1) - xsum[i + 1];
        for (int j = 2; j <= min(i + 1, p); j++) {
            int ptr = i;
            dp[i][j] = INF;
            for (int k = i - 1; k >= j - 2; k--) {
                while (x[ptr] > (x[i] + x[k]) / 2) ptr--;
                int lsum = (xsum[ptr + 1] - xsum[k]) - x[k] * (ptr - k + 1),
                    rsum = x[i] * (i - ptr) - (xsum[i + 1] - xsum[ptr + 1]);
                dp[i][j] = min(dp[i][j], dp[k][j-1] + lsum + rsum);
            }
        }
    }
    for (int i = p - 1; i < v; i++) ans = min(ans, dp[i][p] + xsum[v] - xsum[i] - x[i] * (v - i));
    printf("%d\n", ans);
}