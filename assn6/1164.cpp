#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int map[50][50], room[50][50];
int n, m, cnt;

int dfs(int i, int j) {
    int ret = 1;
    if (!(map[i][j] & 1) && !room[i][j-1]) {
        room[i][j-1] = cnt;
        ret += dfs(i, j-1);
    }
    if (!(map[i][j] & 2) && !room[i-1][j]) {
        room[i-1][j] = cnt;
        ret += dfs(i-1, j);
    }
    if (!(map[i][j] & 4) && !room[i][j+1]) {
        room[i][j+1] = cnt;
        ret += dfs(i, j+1);
    }
    if (!(map[i][j] & 8) && !room[i+1][j]) {
        room[i+1][j] = cnt;
        ret += dfs(i+1, j);
    }
    return ret;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &map[i][j]);
    memset(room, 0, sizeof(room));
    cnt = 0;
    int max_room = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (room[i][j] == 0) {
                cnt++;
                room[i][j] = cnt;
                max_room = max(max_room, dfs(i, j));
            }
    printf("%d\n%d\n", cnt, max_room);
}