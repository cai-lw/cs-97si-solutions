#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;
const int P=1048573;

ll snowflake_hash(int *a) {
    int h1 = 0, h2 = 0;
    for(int i = 0; i < 6; i++) {
        h1 = (h1 * 233 + a[i]) % P;
        h2 = (h2 * 149 + a[i]) % P;
    }
    ll ret = 0;
    for(int i = 0; i < 6; i++) {
        ret ^= (ll(h1) << 20) | h2;
        // 475045=(233^6)%P 439173=(149^6)%P
        h1 = (h1 * 233 + int(ll(P + 1 - 475045) * a[i] % P)) % P;
        h2 = (h2 * 149 + int(ll(P + 1 - 439173) * a[i] % P)) % P;
    }
    return ret;
}

ll h[100000];

int main() {
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        int sf[6];
        scanf("%d%d%d%d%d%d", sf, sf+1, sf+2, sf+3, sf+4, sf+5);
        h[i] = snowflake_hash(sf);
        reverse(sf, sf + 6);
        h[i] ^= snowflake_hash(sf);
    }
    sort(h, h + n);
    for(int i = 0; i < n - 1; i++)
        if(h[i] == h[i+1]) {
            printf("Twin snowflakes found.\n");
            return 0;
        }
    printf("No two snowflakes are alike.\n");
}