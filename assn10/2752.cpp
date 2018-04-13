#include <cstdio>
#include <stack>
using namespace std;

int nxt[400000];
char s[400001];
int main() {
    while(!feof(stdin)) {
        scanf("%s ", s);
        nxt[0] = -1;
        int i;
        for (i = 1; s[i] != '\0'; i++) {
            int j = nxt[i - 1];
            while (s[j + 1] != s[i] && j >= 0) j = nxt[j];
            if (s[j + 1] == s[i]) nxt[i] = j + 1;
            else nxt[i] = -1;
        }
        stack<int> st;
        i--;
        while(i != -1) {
            st.push(i + 1);
            i = nxt[i];
        }
        while(st.size() > 1) {
            printf("%d ", st.top());
            st.pop();
        }
        printf("%d\n", st.top());
    }
}