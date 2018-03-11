#include <cstdio>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

const long BASE = 1000000000;
const int LOG10_BASE = 9;

class big_uint {
    vector<long> digits;
public:
    big_uint(long num) {
        if (num != 0) {
            digits = vector<long>(1, num);
        }
        else {
            digits = vector<long>(0);
        }
    }

    big_uint(vector<long> num):digits(num) {}

    void operator+=(big_uint &other) {
        vector<long> &a = this->digits, &b = other.digits;
        long carry = 0;
        for (int i = 0; i < a.size(); i++) {
            a[i] += carry;
            carry = 0;
            if (i < b.size()) a[i] += b[i];
            if (a[i] >= BASE) {
                carry = 1;
                a[i] -= BASE;
            }
        }
        for (int i = a.size(); i < b.size(); i++) {
            a.push_back(b[i] + carry);
            carry = 0;
            if (a[i] >= BASE) {
                carry = 1;
                a[i] -= BASE;
            }
        }
        if (carry > 0) {
            a.push_back(carry);
        }
    }

    void operator*=(long b) {
        vector<long> &a = this->digits;
        long hi = 0;
        for (int i = 0; i < a.size(); i++) {
            long long digit = (long long)a[i] * b + hi;
            hi = digit / BASE;
            a[i] = digit % BASE;
        }
        if (hi > 0) {
            a.push_back(hi);
        }
    }

    string to_string() {
        vector<long> &a = this->digits;
        if (a.size() == 0) return string("0");
        ostringstream ss;
        ss << a[a.size() - 1] ;
        for (int i = a.size() - 2; i >= 0; i--) {
            ss << setfill('0') << setw(LOG10_BASE) << a[i];
        }
        return ss.str();
    }
};

int main() {
    vector<vector<big_uint> > dp(201, vector<big_uint>(101, big_uint(0)));
    dp[0][0] = big_uint(1);
    for (int i = 1; i <= 200; i++) {
        for (int j = 0; j <= 100; j++) {
            if (j > 0) dp[i][j] += dp[i - 1][j - 1];
            if (j < 100) dp[i][j] += dp[i - 1][j + 1];
        }
    }
    int n;
    scanf("%d", &n);
    while (n > 0) {
        printf("%s\n", dp[n * 2][0].to_string().c_str());
        scanf("%d", &n);
    }
}