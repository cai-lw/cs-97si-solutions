#include <cstdio>
#include <algorithm>
using namespace std;

int n, a[10000], pre[10000];

int main() {
    scanf("%d", &n);
    fill(pre, pre + n, -1);
    int s = 0;
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        s = (s + a[i]) % n;
        if (s == 0) {
            printf("%d\n", i + 1);
            for(int j = 0; j <= i; j++)printf("%d\n", a[j]);
            break;
        }
        else if(pre[s] >= 0) {
            printf("%d\n", i - pre[s]);
            for(int j = pre[s] + 1; j <= i; j++)printf("%d\n", a[j]);
            break;
        }
        else pre[s] = i;
    }
}