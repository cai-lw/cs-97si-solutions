#include <cstdio>
#include <cstring>
using namespace std;

bool board[26][26];
int p, q, depth, xnext[26][26], ynext[26][26];
const int dy[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
const int dx[8] = {-1, 1, -2, 2, -2, 2, -1, 1};

bool dfs(int x, int y) {
    depth++;
    if (depth == p * q) return true;
    board[x][y] = true;
    for (int i = 0; i < 8; i++) {
        int x1 = x + dx[i], y1 = y + dy[i];
        if (x1 >= 0 && x1 < p && y1 >= 0 && y1 < q && !board[x1][y1]) 
            if (dfs(x1, y1)) {
                xnext[x][y] = x1;
                ynext[x][y] = y1;
                return true;
            }
    }
    board[x][y] = false;
    depth--;
    return false;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int cas = 1; cas <= n; cas++) {
        printf("Scenario #%d:\n", cas);
        scanf("%d %d", &p, &q);
        bool ok = false;
        memset(board, 0, sizeof(board));
        depth = 0;
        for(int i = 0; !ok && i < p; i++)
            for (int j = 0; !ok && j < q; j++) {
                if (dfs(i, j)) {
                    ok = true;
                    int x = i, y = j;
                    for (int i = 0; i < p * q; i++) {
                        printf("%c%c", 'A' + y, '1' + x);
                        int x1 = xnext[x][y], y1 = ynext[x][y];
                        x = x1;
                        y = y1;
                    }
                    printf("\n");
                }
            }
        if (!ok) printf("impossible\n");
        if (cas != n) printf("\n");
    }
}