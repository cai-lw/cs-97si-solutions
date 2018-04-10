#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    char sa[11], sb[11];
    while(t--){
        scanf("%s %s", sa, sb);
        reverse(sa, sa + strlen(sa));
        reverse(sb, sb + strlen(sb));
        int c = atoi(sa) + atoi(sb);
        bool leading = true;
        while(c > 0) {
            if(!leading || c % 10 > 0) {
                printf("%d", c % 10);
                leading = false;
            }
            c /= 10;
        }
        printf("\n");
    }
}