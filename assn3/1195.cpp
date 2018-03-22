#include <vector>
#include <cstdio>
using namespace std;

class Bitree2 {
    vector<vector<int> > a;
public:
    Bitree2(int n): a(n + 1, vector<int>(n + 1, 0)) {}
    void add(int i, int j, int d) {
        int j0 = j;
        while (i < a.size()) {
            j = j0;
            while (j < a.size()) {
                a[i][j] += d;
                j += j & (-j);
            }
            i += i & (-i);
        }
    }    
    int sum(int i, int j) {
        int ret = 0, j0 = j;
        while (i > 0) {
            j = j0;
            while (j > 0) {
                ret += a[i][j];
                j -= j & (-j);
            }
            i -= i & (-i);
        }
        return ret;
    }
};

int main() {
    int instr, x, y, a, b;
    Bitree2 tr(1024);
    do {
        scanf("%d", &instr);
        if (instr == 0) {
            scanf("%d", &x);
        }
        else if (instr == 1) {
            scanf("%d %d %d", &x, &y, &a);
            tr.add(x + 1, y + 1, a);
        }
        else if (instr == 2) {
            scanf("%d %d %d %d", &x, &y, &a, &b);
            printf("%d\n", tr.sum(a + 1, b + 1) - tr.sum(x, b + 1) - tr.sum(a + 1, y) + tr.sum(x, y));
        }
    } while (instr != 3);
}