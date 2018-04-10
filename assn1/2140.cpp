#include <cstdio>
using namespace std;

int main() {
    int n, i, cnt = 0;
    scanf("%d", &n);
    while(n % 2 == 0) n /= 2;
    for(i = 1; i * i < n; i += 2)
        if(n % i == 0) cnt += 2;
    if(i * i == n) cnt += 1;
    printf("%d\n", cnt);
}