#include <cstdio>
#include <algorithm>
using namespace std;

bool le(int *a, int *b) {
    for(int i = 0; i < 6; i++) {
        if(a[i] < b[i]) return true;
        if(a[i] > b[i]) return false;
    }
    return false;
}

bool eq(int *a, int *b) {
    for(int i = 0; i < 6; i++)
        if(a[i] != b[i]) return false;
    return true;
}

void snowflake(int *a) {
    int m[6];
    copy(a, a+6, m);
    for(int i = 1; i < 6; i++) {
        for(int j = 0; j < 5; j++)swap(a[j],a[j+1]);
        if(le(a, m))copy(a, a+6, m);
    }
    for(int i = 0; i < 3; i++)swap(a[i], a[5-i]);
    if(le(a, m))copy(a, a+6, m);
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++)swap(a[j],a[j+1]);
        if(le(a, m))copy(a, a+6, m);
    }
    copy(m, m+6, a);
}

int snowflake_hash(int *a) {
    int ret = 0;
    for(int i = 0; i < 6; i++) ret = (ret * 131 + a[i]) % 1048576;
    return ret;
}

int hashmap[1048576][10];
int s[600000];

int main() {
    for(int i = 0; i < 1048576; i++)
        for(int j = 0; j < 10; j++) hashmap[i][j] = -1;
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 6; j++)scanf("%d", &s[i*6+j]);
        snowflake(s+i*6);
        int h = snowflake_hash(s+i*6);
        int pt;
        for(pt = 0; hashmap[h][pt] != -1; pt++){;
            if(eq(s+i*6, s+hashmap[h][pt]*6)){
                printf("Twin snowflakes found.\n");
                return 0;
            }
        }
        hashmap[h][pt] = i;
    }
    printf("No two snowflakes are alike.\n");
}