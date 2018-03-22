#include <cstdio>
#include <algorithm>
using namespace std;

int main() {
    int dp[101][100], n, a, ans=0;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            scanf("%d", &a);
            if (i == 1) dp[i][j] = a;
            else if (j == 0) dp[i][j] = dp[i-1][j] + a;
            else if (j == i - 1) dp[i][j] = dp[i-1][j-1] + a;
            else dp[i][j] = max(dp[i-1][j-1], dp[i-1][j]) + a;
        }
    }
    for (int j = 0; j < n; j++) ans = max(ans, dp[n][j]);
    printf("%d\n", ans);
}