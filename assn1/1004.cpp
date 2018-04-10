#include <cstdio>
using namespace std;

int main() {
    int n = 0;
    double x, tot = 0.0;
    while(!feof(stdin)) {
        scanf("%lf ", &x);
        tot += x;
        n++;
    }
    printf("$%.2lf\n", tot / n);
}