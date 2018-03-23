#include <cstdio>

int main() {
    int n;
    scanf("%d", &n);
    while (n > 0) {
        printf(n <= 2 ? "Alice\n" : "Bob\n");
        scanf("%d", &n);
    }
}