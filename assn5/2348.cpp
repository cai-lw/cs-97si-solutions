#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

void find_seq(int x, int y, vector<int> &seq) {
    if (y == 0) return;
    seq.push_back(x / y);
    find_seq(y, x % y, seq);
}

int main() {
    int x, y;
    scanf("%d %d", &x, &y);
    while (x > 0 && y > 0) {
        if (x < y) swap(x, y);
        vector<int> seq;
        find_seq(x, y, seq);
        bool win = true;
        for (int i = seq.size() - 2; i >= 0; i--) {
            win = !(win && seq[i] == 1);
        }
        printf(win ? "Stan wins\n" : "Ollie wins\n");
        scanf("%d %d", &x, &y);
    }
}