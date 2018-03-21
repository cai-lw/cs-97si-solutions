#include <vector>
#include <stack>
#include <cstdio>
using namespace std;

class Bitree {
    vector<int> a;
public:
    Bitree(int n): a(n + 1, 0) {}
    void all_one() {
        for (int i = 1; i < a.size(); i++) a[i] = i & (-i);
    }
    void change(int i, int d) {
        while (i < a.size()) {
            a[i] += d;
            i += i & (-i);
        }
    }    
    int sum(int i) {
        int ret = 0;
        while (i > 0) {
            ret += a[i];
            i -= i & (-i);
        }
        return ret;
    }
};

int main() {
    int n, m;
    scanf("%d", &n);
    vector<vector<int> > ch(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        ch[u].push_back(v);
        ch[v].push_back(u);
    }
    vector<int> left(n + 1), right(n + 1), ptr(n + 1, 0);
    vector<bool> vis(n + 1, false), apple(n + 1, true);
    int i = 1;
    stack<int> st;
    st.push(1);
    left[1] = 1;
    vis[1] = true;
    while (!st.empty()) {
        int u = st.top();
        if (ptr[u] >= ch[u].size()) {
            right[u] = i;
            st.pop();
        }
        else {
            int v = ch[u][ptr[u]];
            if (!vis[v]) {
                vis[v] = true;
                st.push(v);
                i++;
                left[v] = i;
            }
            ptr[u]++;
        }
    }
    Bitree tr(n);
    tr.all_one();
    scanf("%d", &m);
    while (m--) {
        char op;
        int x;
        scanf(" %c %d", &op, &x);
        if (op == 'C') {
            tr.change(left[x], apple[x] ? -1 : 1);
            apple[x] = !apple[x];
        }
        else printf("%d\n", tr.sum(right[x]) - tr.sum(left[x] - 1));
    }
}