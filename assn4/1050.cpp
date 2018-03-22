#include <cstdio>
int a[100][100], sum[101][101], dp[101][101][101];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            scanf("%d", &a[i][j]);
            sum[i+1][j+1] = sum[i+1][j] + sum[i][j+1] - sum[i][j] + a[i][j];
        }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++) {
            dp[i][j][1] = sum[j][1] - sum[i-1][1];
            for (int k = 1; k <= n; k++) {
                dp[i][j][k] = sum[j][k] - sum[i-1][k] - sum[j][k-1] + sum[i-1][k-1];
                if (dp[i][j][k-1] > 0) dp[i][j][k] += dp[i][j][k-1];
                if (dp[i][j][k] > ans) ans = dp[i][j][k];
            }
        }
    if (ans == 0) {
        ans = -1000000000;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (ans < a[i][j]) ans = a[i][j];
    }
    printf("%d\n", ans);
}