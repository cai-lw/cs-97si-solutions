#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int main() {
    int m, k;
    scanf("%d", &k);
    while (k > 0) {
        int s[100], nim[10001];
        for (int i = 0; i < k; i++) scanf("%d", &s[i]);
        sort(s, s + k);
        for (int i = 0; i <= 10000; i++) {
            bool found[101];
            memset(found, 0, sizeof(found));
            for (int j = 0; j < k; j++)
                if (i >= s[j]) found[nim[i - s[j]]] = true;
                else break;
            for (int j = 0; j <= k; j++)
                if (!found[j]) {
                    nim[i] = j;
                    break;
                }
        }
        scanf("%d", &m);
        while (m--) {
            int n, h, game = 0;
            scanf("%d", &n);
            for (int i = 0; i < n; i++) {
                scanf("%d", &h);
                game ^= nim[h];
            }
            printf(game ? "W" : "L");
        }
        printf("\n");
        scanf("%d", &k);
    }
}