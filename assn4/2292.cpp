#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;

inline int ord(char c) {
    if (c >= 'a') return c - 'a';
    switch (c) {
        case '+': return 26; break;
        case '*': return 27; break;
        case '/': return 28; break;
        case '?': return 29; break;
    }
}

char chr(int i) {
    if (i < 26) return 'a' + i;
    return "+*/?"[i - 26];
}

int main() {
    int n, t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        int cnt[30], sum_cnt[30], dp[13][30], prev[13][30];
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < n; i++) {
            char s[31];
            scanf("%s", s);
            for(int i = 0; s[i] != '\0'; i++) cnt[ord(s[i])]++;
        }
        sum_cnt[0] = cnt[0];
        for (int i = 1; i < 30; i++) sum_cnt[i] = sum_cnt[i-1] + cnt[i];
        dp[1][0] = cnt[0];
        for (int i = 1; i < 30; i++) dp[1][i] = dp[1][i-1] + (i + 1) * cnt[i];
        for (int i = 2; i <= 12; i++)
            for (int j = i - 1; j < 30; j++) {
                dp[i][j] = 1000000000;
                int cost = 0;
                for (int k = j - 1; k >= i - 2; k--) {
                    cost += sum_cnt[j] - sum_cnt[k];
                    if (dp[i-1][k] + cost <= dp[i][j]) {
                        dp[i][j] = dp[i-1][k] + cost;
                        prev[i][j] = k;
                    }
                }
            }
        string ans;
        int j = 29;
        for (int i = 12; i > 1; i--) {
            j = prev[i][j];
            ans += chr(j+1);
        }
        reverse(ans.begin(), ans.end());
        printf("%s\n", ans.c_str());
    }
}