#include <cstdio>
#include <vector>
#include <algorithm>
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

struct Edge {
    int u, v, w;
    Edge() {}
    Edge(int u, int v, int w): u(u), v(v), w(w) {}
    bool operator<(const Edge &other) const {
        return w < other.w;
    }
};

int main() {
    int n;
    while (scanf("%d", &n) != EOF) {
        vector<Edge> edges;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                int w;
                scanf("%d", &w);
                if (i < j) edges.push_back(Edge(i, j, w));
            }
        sort(edges.begin(), edges.end());
        int count = 0, ans = 0;
        Ufs ufs(n);
        for (int i = 0; i < edges.size(); i++) {
            Edge &e = edges[i];
            if (ufs.find(e.u) != ufs.find(e.v)) {
                ufs.merge(e.u, e.v);
                count += 1;
                ans += e.w;
                if (count >= n - 1) break;
            }
        }
        printf("%d\n", ans);
    }
}