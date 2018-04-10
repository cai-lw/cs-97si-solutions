#include <cstdio>
#include <algorithm>
using namespace std;

int main() {
    int n, t;
    scanf("%d", &t);
    for(int cas = 1; cas <= t; cas++) {
        scanf("%d", &n);
        printf("Scenario #%d:\n", cas);
        for(int i = -n; i <= n; i++) {
            printf("slice #%d:\n", i + n + 1);
            for(int j = -n; j <= n; j++) {
                for(int k = -n; k <= n; k++) {
                    int d = abs(i) + abs(j) + abs(k);
                    if (d <= n) printf("%d", d);
                    else printf(".");
                }
                printf("\n");
            }
        }
        if (cas < t) printf("\n");
    }
}