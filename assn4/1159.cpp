#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    char s[5001];
    scanf("%d", &n);
    scanf("%s", s);
    vector<int> dp(n + 1, 0), prev(n + 1, 0);
    for (int j = n - 1; j >= 0; j--) {
        for (int i = 0; i < n; i++) {
            dp[i+1] = max(dp[i], prev[i+1]);
            if (s[i] == s[j]) dp[i+1] = max(dp[i+1], prev[i] + 1);
        }
        prev = dp;
    }
    printf("%d\n", n - dp[n]);
}