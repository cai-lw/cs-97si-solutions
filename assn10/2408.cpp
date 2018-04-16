#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct Entry {
    string orig, sorted, repr;
    int cnt;
};

bool cmp1(const Entry &a, const Entry &b) {
    return a.orig < b.orig;
}

bool cmp2(const Entry &a, const Entry &b) {
    return a.sorted < b.sorted;
}

bool cmp3(const Entry &a, const Entry &b) {
    return a.cnt > b.cnt || (a.cnt == b.cnt && a.repr < b.repr);
}

Entry a[30000];

int main() {
    int n = 0;
    while(!cin.eof()) {
        Entry &entry = a[n];
        cin >> entry.orig >> ws;
        entry.sorted = entry.orig;
        sort(entry.sorted.begin(), entry.sorted.end());
        entry.cnt = 0;
        n++;
    }
    sort(a, a + n, cmp1);
    stable_sort(a, a + n, cmp2);
    int i = 0;
    while(i < n) {
        int j = i + 1;
        while(j < n && a[i].sorted == a[j].sorted) j++;
        for(int k = i; k < j; k++) {
            a[k].cnt = j - i;
            a[k].repr = a[i].orig;
        }
        i = j;
    }
    stable_sort(a, a + n, cmp3);
    int group = 0;
    for(int i = 0; i < n; i++) {
        if(i == 0 || a[i].sorted != a[i-1].sorted) {
            if(group >= 5) {
                cout << '.' << endl;
                break;
            }
            group++;
            if(i > 0) cout << '.' << endl;
            cout << "Group of size " << a[i].cnt << ": ";
        }
        if(i == 0 || a[i].orig != a[i-1].orig) {
            cout << a[i].orig << ' ';
        }
    }
}