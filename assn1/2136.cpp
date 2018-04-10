#include <cstdio>
using namespace std;

int main() {
    int cnt[26] = {0}, max_cnt = 0;
    char buf[75];
    for(int i = 0; i < 4; i++) {
        fgets(buf, 75, stdin);
        for(int i = 0; buf[i] != '\0'; i++)
            if(buf[i] >= 'A' && buf[i] <= 'Z') {
                cnt[buf[i] - 'A']++;
                if(max_cnt < cnt[buf[i] - 'A']) max_cnt++;
            }
    }
    for(int i = max_cnt; i > 0; i--) {
        int prev = -1;
        for(int j = 0; j < 26; j++) {
            if(cnt[j] >= i) {
                for(int k = prev + 1; k < j; k++) printf("  ");
                if(prev == -1) printf("*"); else printf(" *");
                prev = j;
            }
        }
        printf("\n");
    }
    for(int i = 0; i < 25; i++) printf("%c ", char('A' + i));
    printf("Z\n");
}