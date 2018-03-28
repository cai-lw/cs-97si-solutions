#include <cstdio>
#include <algorithm>
using namespace std;

bool num[10001];
int dp[10001];

const int MINF = -1000000000;

int main() {
    int n, a, b, t, x;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d %d", &n, &a, &b);
        fill(num, num + 10001, false);
        for(int i = 0; i < n; i++) {
            scanf("%d", &x);
            if (x > 0) num[x] = true;
        }
        for (int i = 10000; i > 0; i--) {
            if (!num[i]) continue;
            int player2 = MINF;
            for (int j = a; j <= min(10000-i, b); j++)
                if (num[i + j]) player2 = max(player2, dp[i + j]);
            if (player2 == MINF) dp[i] = i;
            else dp[i] = i - player2;
        }
        int ans = MINF;
        for (int i = a; i <= b; i++)
            if (num[i]) ans = max(ans, dp[i]);
        printf("%d\n", ans == MINF ? 0 : ans);
    }
}