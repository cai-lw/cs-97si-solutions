#include <string>
#include <cstring>
#include <map>
#include <algorithm>
#include <cstdio>
using namespace std;

int main() {
    map<string, int> m;
    int count = 0;
    while(!feof(stdin)) {
        char buf[31];
        if(fgets(buf, 30, stdin) == NULL) break;
        int len = strlen(buf);
        if (len > 0 && buf[len - 1] == '\n') len--;
        count++;
        string s(buf, len);
        if (m.count(s) == 0) m[s] = 1;
        else m[s] += 1;
    }
    for (map<string, int>::iterator it = m.begin(); it != m.end(); it++) {
        printf("%s %.4f\n", it->first.c_str(), float(it->second * 100) / count);
    }
}