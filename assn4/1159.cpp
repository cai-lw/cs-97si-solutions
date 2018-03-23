#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int main() {
    int n, a1[5001], a2[5001];
    memset(a1, 0, sizeof(a1));
    memset(a2, 0, sizeof(a2));
    char s[5001];
    scanf("%d", &n);
    scanf("%s", s);
    int *dp = a1, *prev = a2;
    for (int j = n - 1; j >= 0; j--) {
        for (int i = 0; i < n; i++) {
            dp[i+1] = max(dp[i], prev[i+1]);
            if (s[i] == s[j]) dp[i+1] = max(dp[i+1], prev[i] + 1);
        }
        swap(prev, dp);
    }
    printf("%d\n", n - prev[n]);
}