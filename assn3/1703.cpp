#include <vector>
#include <cstdio>
using namespace std;

class Ufs {
    vector<int> par, rank;
public:
    Ufs(int n): par(n, -1), rank(n, 0) {}
    int find(int i) {
        if (par[i] == -1) return i;
        par[i] = find(par[i]);
        return par[i];
    }
    void merge(int i, int j) {
        i = find(i);
        j = find(j);
        if (i == j) return;
        if (rank[i] < rank[j]) par[i] = j;
        else {
            par[j] = i;
            if (rank[i] == rank[j]) rank[i]++;
        }
    }
};

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, m, i, j;
        scanf("%d %d", &n, &m);
        Ufs ufs(n * 2);
        while (m--) {
            char op;
            scanf(" %c %d %d", &op, &i, &j);
            if (op == 'D') {
                ufs.merge(i - 1, j - 1 + n);
                ufs.merge(j - 1, i - 1 + n);
            }
            else if (op == 'A') {
                if (ufs.find(i - 1) == ufs.find(j - 1)) printf("In the same gang.\n");
                else if (ufs.find(i - 1) == ufs.find(j - 1 + n)) printf("In different gangs.\n");
                else printf("Not sure yet.\n");
            }
        }
    }
}