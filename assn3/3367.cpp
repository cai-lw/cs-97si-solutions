#include <string>
#include <stack>
#include <queue>
#include <algorithm>
#include <iostream>
#include <ios>
using namespace std;

struct Exp {
    char c;
    int l, r;
    Exp() {}
    Exp(char c): c(c), l(-1), r(-1) {}
};

int build(string &s, vector<Exp> &pool) {
    stack<int> st;
    int ptr = 0;
    for(int i = 0; i < s.length(); i++) {
        pool[ptr] = Exp(s[i]);
        if (s[i] < 'a') {
            pool[ptr].l = st.top();
            st.pop();
            pool[ptr].r = st.top();
            st.pop();
        }
        st.push(ptr);
        ptr++;
    }
    return st.top();
}

string serialize(int t, vector<Exp> &pool) {
    queue<int> q;
    string ret;
    q.push(t);
    while (!q.empty()) {
        t = q.front();
        q.pop();
        ret += pool[t].c;
        if (pool[t].r >= 0) q.push(pool[t].r);
        if (pool[t].l >= 0) q.push(pool[t].l);
    }
    reverse(ret.begin(), ret.end());
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    while (n--) {
        string s;
        cin >> s;
        vector<Exp> pool(s.length());
        int t = build(s, pool);
        cout << serialize(t, pool) << endl;
    }
}