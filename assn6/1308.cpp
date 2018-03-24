#include <cstdio>
#include <map>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

int main() {
    int u, v, t = 0;
    scanf("%d %d", &u, &v);
    while (u >= 0) {
        t++;
        map<int, int> deg;
        map<int, bool> vis;
        map<int, vector<int> > graph;
        while (u > 0) {
            if (deg.count(u) == 0) deg[u] = 0;
            if (deg.count(v) == 0) deg[v] = 0;
            graph[u].push_back(v);
            deg[v]++;
            vis[u] = false;
            vis[v] = false;
            scanf("%d %d", &u, &v);
        }
        bool ok = true;
        int root = 0;
        for (map<int, int>::iterator it = deg.begin(); it != deg.end(); it++)
            if (it->second > 1) {
                ok = false;
                break;
            }
            else if (it->second == 0) {
                if (root > 0) {
                    ok = false;
                    break;
                }
                else root = it->first;
            }
        if (ok) {
            queue<int> q;
            q.push(root);
            vis[root] = true;
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                vector<int> &vs = graph[u];
                for (int i = 0; i < vs.size(); i++) {
                    int v = vs[i];
                    if (!vis[v]) {
                        vis[v] = true;
                        q.push(v);
                    }
                }
            }
            for (map<int, bool>::iterator it = vis.begin(); it != vis.end(); it++)
                if (!it->second) {
                    ok = false;
                    break;
                }
        }
        if (ok) printf("Case %d is a tree.\n", t);
        else printf("Case %d is not a tree.\n", t);
        scanf("%d %d", &u, &v);
    }
}