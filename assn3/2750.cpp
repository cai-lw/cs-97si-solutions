#include <cstdio>
#include <algorithm>
using namespace std;

struct Node {
    int s, ls, rs, ms, mn;
};

class SegTree {
    Node *tree;
    int offset, guard;
    void maintain(int i) {
        int l = i * 2, r = i * 2 + 1;
        tree[i].s = tree[l].s + tree[r].s;
        tree[i].ls = max(tree[l].ls, tree[l].s + tree[r].ls);
        tree[i].rs = max(tree[r].rs, tree[r].s + tree[l].rs);
        tree[i].ms = max(tree[l].rs + tree[r].ls, max(tree[l].ms, tree[r].ms));
        tree[i].mn = min(tree[l].mn, tree[r].mn);
    }
public:
    SegTree(int n, int *a) {
        offset = 1;
        while(offset < n) offset *= 2;
        tree = new Node[offset * 2];
        guard = offset + n;
        for(int i = offset; i < offset * 2; i++) {
            int x = (i >= offset + n) ? 0 : a[i - offset];
            tree[i].s = x;
            tree[i].ls = x;
            tree[i].rs = x;
            tree[i].ms = x;
            tree[i].mn = (i >= offset + n) ? 10000 : a[i - offset];
        }
        for(int i = offset - 1; i > 0; i--) maintain(i);
    }
    void update(int i, int x) {
        int idx = offset + i;
        tree[idx].s = x;
        tree[idx].ls = x;
        tree[idx].rs = x;
        tree[idx].ms = x;
        tree[idx].mn = x;
        for(idx >>= 1; idx > 0; idx >>= 1) maintain(idx);
    }
    Node root() {
        return tree[1];
    }
};

int main() {
    int n, m, k, x, a[100000];
    scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%d", &a[i]);
    SegTree tpos(n, a);
    for(int i = 0; i < n; i++) a[i] = -a[i];
    SegTree tneg(n, a);
    scanf("%d", &m);
    for(int i = 0; i < m; i++) {
        scanf("%d %d", &k, &x);
        tpos.update(k-1, x);
        tneg.update(k-1, -x);
        int ans = max(tpos.root().ms, tneg.root().ms - tneg.root().s);
        if (ans == tpos.root().s) ans -= tpos.root().mn;
        printf("%d\n", ans);
    }
}