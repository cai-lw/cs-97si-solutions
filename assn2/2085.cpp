#include <cstdio>
#include <deque>
using namespace std;

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    while (n > 0) {
        deque<int> q(n);
        for (int i = 1; i <= n; i++){
            q[i - 1] = i;
        }
        while (n > 0) {
            int out, remaining = (unsigned int)(n - 1) * (n - 2) / 2;
            if (n == 1 || m <= remaining) {
                out = q.front();
                q.pop_front();
            }
            else {
                int idx = m - remaining;
                if (idx == n - 1) {
                    out = q.back();
                    q.pop_back();
                }
                else {
                    out = q[idx];
                    q.erase(q.begin() + idx);
                }
                m = remaining;
            }
            n--;
            if (n == 0) printf("%d\n", out);
            else printf("%d ", out);
        }
        scanf("%d %d", &n, &m);
    }
}