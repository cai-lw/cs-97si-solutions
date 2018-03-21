#include <vector>
#include <stack>
#include <string>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cstdio>
#include <sstream>
using namespace std;

struct Entry {
    string v;
    int k;
    bool operator<(Entry &other) {
        return v < other.v;
    }
};

void print(int i, vector<Entry> &a, vector<int> &l, vector<int> &r, ostringstream &ss) {
    ss << '(';
    if (l[i] >= 0) print(l[i], a, l, r, ss);
    ss << a[i].v << '/' << a[i].k;
    if (r[i] >= 0) print(r[i], a, l, r, ss);
    ss << ')';
}

int main() {
    int n;
    scanf("%d", &n);
    while (n > 0) {
        vector<Entry> a(n);
        vector<int> l(n, -1), r(n, -1), p(n, -1);
        for (int i = 0; i < n; i++) {
            char buf[1000000];
            scanf("%s", buf);
            char* sep = strchr(buf, '/');
            a[i].v = string(buf, sep - buf);
            a[i].k = atoi(sep + 1);
        }
        sort(a.begin(), a.end());
        stack<int> st;
        for (int i = 0; i < n; i++) {
            while (!st.empty() && a[st.top()].k < a[i].k) st.pop();
            if (!st.empty()) {
                r[st.top()] = i;
                p[i] = st.top();
            }
            st.push(i);
        }
        st = stack<int>();
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && a[st.top()].k < a[i].k) st.pop();
            if (!st.empty()) {
                l[st.top()] = i;
                p[i] = st.top();
            }
            st.push(i);
        }
        ostringstream ss;
        for (int i = 0; i < n; i++)
            if (p[i] == -1) {
                print(i, a, l, r, ss);
                break;
            }
        printf("%s\n", ss.str().c_str());
        scanf("%d", &n);
    }
}