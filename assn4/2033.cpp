#include <cstdio>

int main() {
    char s[100000];
    int dp[100000];
    scanf("%s", s);
    while (s[0] != '0') {
        dp[0] = 1;
        int i;
        for (i = 1; s[i] != '\0'; i++) {
            dp[i] = s[i] == '0' ? 0 : dp[i-1];
            if (s[i-1] > '0' && (s[i-1] - '0') * 10 + s[i] - '0' <= 26) dp[i] += i < 2 ? 1 : dp[i-2];
        }
        printf("%d\n", dp[i-1]);
        scanf("%s", s);
    }
}
