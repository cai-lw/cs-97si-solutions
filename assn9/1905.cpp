#include <cstdio>
#include <cmath>

int main() {
    double l, n, c;
    scanf("%lf %lf %lf", &l, &n, &c);
    while(l >= 0) {
        if (l == 0.0 || n == 0.0 || c == 0.0) printf("0.000\n");
        else {
            double lo = 0.0, hi = l / 2;
            while (true) {
                double h = (lo + hi) / 2;
                if (h == lo || h == hi || h < 5e-4) {
                    printf("%.3lf\n", h);
                    break;
                }
                double r = (l * l / 4 + h * h) / (h * 2),
                       len = atan(h * 2 / l) * 4 * r;
                if (len >= l * (1 + n * c)) hi = h;
                else lo = h;
            }
        }
        scanf("%lf %lf %lf", &l, &n, &c);
    }
}