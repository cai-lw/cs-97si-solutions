#include <vector>
#include <utility>
#include <cstdio>
using namespace std;

class Ufs {
    vector<int> par, down, up;
public:
    Ufs(int n): par(n, -1), down(n, 0), up(n, 1) {}
    pair<int, int> find(int i) {
        if (par[i] == -1) return make_pair(i, 0);
        pair<int, int> p = find(par[i]);
        par[i] = p.first;
        down[i] += p.second;
        return make_pair(par[i], down[i]);
    }
    void stack(int i, int j) {
        i = find(i).first;
        j = find(j).first;
        par[i] = j;
        down[i] += up[j];
        up[j] += up[i];
    }
};

int main() {
    Ufs ufs(30001);
    int p;
    scanf("%d", &p);
    while (p--) {
        int i, j;
        char op;
        scanf(" %c", &op);
        if (op == 'M') {
            scanf("%d %d", &i, &j);
            ufs.stack(i, j);
        }
        else if (op == 'C') {
            scanf("%d", &i);
            printf("%d\n", ufs.find(i).second);
        }
    }
}