#include <cstdio>

int main() {
    int dp[31][8], n;
    dp[0][7] = 1;
    for (int j = 0; j < 7; j++) dp[0][j] = 0;
    for (int i = 1; i <= 30; i++) {
        for (int j = 0; j < 8; j++) {
            dp[i][j] = dp[i-1][7 ^ j];
            if ((j & 6) == 6) dp[i][j] += dp[i-1][1 ^ j];
            if ((j & 3) == 3) dp[i][j] += dp[i-1][4 ^ j];
        }
    }
    scanf("%d", &n);
    while (n >= 0) {
        printf("%d\n", dp[n][7]);
        scanf("%d", &n);
    }
}