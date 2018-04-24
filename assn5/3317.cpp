#include <cstdio>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

int state[59049], mov[59049], x[10], y[10], n, h;
char board[8][9];
bool vis[8][8];

int score(int st, int player) {
    for(int i = 0; i < h; i++) {
        board[x[i]][y[i]] = '0' + (st % 3 - 1);
        st /= 3;
    }
    for(int i = 0; i < n; i++) fill(vis[i], vis[i] + n, false);
    int sc[2] = {0, 0};
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if (!vis[i][j]) {
                int cnt = 0;
                queue<pair<int, int> > q;
                q.push(make_pair(i, j));
                while(!q.empty()) {
                    cnt++;
                    int pi = q.front().first, pj = q.front().second;
                    q.pop();
                    if(pi > 0 && !vis[pi-1][pj] && board[pi][pj] == board[pi-1][pj]) {
                        vis[pi-1][pj] = true;
                        q.push(make_pair(pi-1, pj));
                    }
                    if(pi < n-1 && !vis[pi+1][pj] && board[pi][pj] == board[pi+1][pj]) {
                        vis[pi+1][pj] = true;
                        q.push(make_pair(pi+1, pj));
                    }
                    if(pj > 0 && !vis[pi][pj-1] && board[pi][pj] == board[pi][pj-1]) {
                        vis[pi][pj-1] = true;
                        q.push(make_pair(pi, pj-1));
                    }
                    if(pj < n-1 && !vis[pi][pj+1] && board[pi][pj] == board[pi][pj+1]) {
                        vis[pi][pj+1] = true;
                        q.push(make_pair(pi, pj+1));
                    }
                }
                sc[board[i][j] - '0'] = max(sc[board[i][j] - '0'], cnt);
            }
    for(int i = 0; i < h; i++) board[x[i]][y[i]] = '.';
    return sc[player] - sc[1-player];
}

int dfs(int st, int player) {
    if(state[st] > -100) return state[st];
    int pow3 = 1;
    bool tried = false;
    for(int i = 0; i < h; i++) {
        if (st % (pow3 * 3) / pow3 == 0) {
            tried = true;
            int newval = -dfs(st + pow3 * (player + 1), 1 - player);
            if (newval > state[st]) {
                mov[st] = i;
                state[st] = newval;
            }
        }
        pow3 *= 3;
    }
    if(!tried) state[st] = score(st, player);
    return state[st];
}

int main() {
    scanf(" %d", &n);
    while(n > 0) {
        h = 0;
        for(int i = 0; i < n; i++) {
            scanf(" %s", board[i]);
            for(int j = 0; j < n; j++)
                if(board[i][j] == '.') {
                    x[h] = i;
                    y[h] = j;
                    h++;
                }
        }
        fill(state, state + 59049, -100);
        dfs(0, (n * n - h) % 2);
        printf("(%d,%d) %d\n", x[mov[0]], y[mov[0]], state[0]);
        scanf(" %d", &n);
    }
}