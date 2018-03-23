#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;
typedef unsigned int ui;
const ll MAX = 4294967296;

int main() {
    vector<ui> a;
    for(ll pw2 = 1; pw2 < MAX; pw2 *= 2)
        for (ll pw3 = 1; pw2 * pw3 < MAX; pw3 *= 3)
            for (ll pw5 = 1; pw2 * pw3 * pw5 < MAX; pw5 *= 5)
                for (ll pw7 = 1; pw2 * pw3 * pw5 * pw7 < MAX; pw7 *= 7)
                    a.push_back(pw2 * pw3 * pw5 * pw7);
    sort(a.begin(), a.end());
    printf("%d",a.size());
    vector<bool> win(a.size());
    ui n;
    while (scanf("%d", &n) != EOF) {
        int imax = lower_bound(a.begin(), a.end(), n) - a.begin();
        for (int i = imax - 1; i >= 0; i--) {
            if (a[i] >= (n - 1) / 9 + 1) {
                win[i] = true;
                continue;
            }
            win[i] = false;
            for (int j = 9; j >= 2; j--) { 
                ui next = a[i] * j;
                int inext = lower_bound(a.begin(), a.end(), next) - a.begin();
                if (!win[inext]) {
                    win[i] = true;
                    break;
                }
            }
        }
        printf(win[0] ? "Stan wins.\n" : "Ollie wins.\n");
    }
}