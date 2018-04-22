#include <cstdio>
using namespace std;

int main() {
    double d;
    scanf("%lf", &d);
    while(d > 0) {
        int n = 0;
        double l = 0.0;
        while (l < d) {
            n++;
            l += 1.0 / (n+1);
        }
        printf("%d card(s)\n", n);
        scanf("%lf", &d);
    }
}