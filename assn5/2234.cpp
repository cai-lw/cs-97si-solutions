#include <cstdio>

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        int a, nim = 0;
        while (n--) {
            scanf("%d", &a);
            nim ^= a;
        }
        printf(nim ? "Yes\n" : "No\n");
    }
}