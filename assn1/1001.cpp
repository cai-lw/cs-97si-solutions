#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

int main() {
    while(!feof(stdin)) {
        char num[7], out[130];
        int n, dec;
        ll x = 0, ans[25] = {0};
        scanf("%s %d ", num, &n);
        for(int i = 0; i < 6; i++) {
            if(num[i] == '.') dec = 5 - i;
            else x = x * 10 + (num[i] - '0');
        }
        dec *= n;
        ans[0] = x;
        for(int i = 1; i < n; i++) {
            ll carry = 0;
            for(int j = 0; j <= i; j++) {
                ans[j] = ans[j] * x + carry;
                carry = ans[j] / 100000;
                ans[j] %= 100000;
            }
        }
        for(int i = 0; i < n; i++) {
            sprintf(out + 5 * i, "%05lld", ans[n-i-1]);
        }
        int head = 0;
        while(head < 5*n-dec && out[head] == '0') head++;
        int tail = 5 * n;
        while(tail > 5*n-dec && out[tail-1] == '0') tail--;
        for(int i = head; i < 5*n-dec; i++)putchar(out[i]);
        if(tail != 5*n-dec) {
            putchar('.');
            for(int i = 5*n-dec; i < tail; i++)putchar(out[i]);
        }
        putchar('\n');
    }
}