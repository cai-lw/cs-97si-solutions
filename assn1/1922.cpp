#include <cstdio>
#include <cmath>
using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    while (n > 0) {
        int v, t, tmin = 2147483647;
        for(int i = 0; i < n; i++) {
            scanf("%d %d", &v, &t);
            int t1 = 16199/v+t+1;
            if (t >= 0 && tmin > t1) tmin = t1;
        }
        printf("%d\n", tmin);
        scanf("%d", &n);
    }
}