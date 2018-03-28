#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int state[524288];

void dfs(int st);

bool move(int st, int mv) {
    st |= (1 << (mv - 2));
    for (int j = mv + 2; j <= 20; j++)
        st |= (st & (1 << (j - mv - 2))) << mv;
    if (state[st] == 0) dfs(st);
    return state[st] == 1;
}

void dfs(int st) {
    bool win = false;
    for (int i = 2; i <= 20; i++) {
        if (st & (1 << (i - 2))) continue;
        if (!move(st, i)) {
            win = true;
            break;
        }
    }
    state[st] = win ? 1 : -1;
}

vector<int> solve(int st) {
    vector<int> ret;
    for (int i = 2; i <= 20; i++) {
        if (st & (1 << (i - 2))) continue;
        if (!move(st, i)) ret.push_back(i);
    }
    return ret;
}

int main() {
    fill(state, state + 524288, 0);
    for (int i = 0; i < 524288; i++)
        if (state[i] == 0) dfs(i);
    int n, a, cas = 0;
    scanf("%d", &n);
    while (n > 0) {
        int init = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &a);
            init |= 1 << (a - 2);
        }
        init ^= 0x7FFFF;
        vector<int> ans = solve(init);
        printf("Test Case #%d\n", ++cas);
        if (ans.size() == 0) {
            printf("There's no winning move.\n");
        }
        else {
            printf("The winning moves are:");
            for (int i = 0; i < ans.size(); i++)
                printf(" %d", ans[i]);
            printf("\n");
        }
        scanf("%d", &n);
        if (n > 0) printf("\n");
    }
}