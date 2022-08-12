#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
#include <iomanip>
#include <complex>
#include <queue>
#include <cassert>
#include <stack>
#include <random>
#include <chrono>
#include <bitset>
#include <map>
#define forn(i, n) for (int i = 0; i < n; ++i)
#define all(a) begin(a), end(a)
#define int long long
#define sqr(x) ((x) * (x))

#ifndef _debug
    #define debug(...) 42
    #define debr(...) 42
#else
    #define debug(x) cout << #x << " = " << x << endl
    #define debr(...) { cout << #__VA_ARGS__ << " = ";  _debr(__VA_ARGS__); }
#endif

using namespace std;

template<class Iter> 
void _debr(Iter l, Iter r) {
    cout << "[";
    for (auto it = l; it != r; ++it) {
        if (it != l) {
            cout << ", ";   
        }
        cout << *it;
    }
    cout << "]" << endl;
}

template<class C, class F> 
ostream& operator<<(ostream &out, pair<C, F> p) {
    return out << "(" << p.first << ", " << p.second << ")";
}

using ll = long long;

mt19937_64 rnd(std::chrono::system_clock::now().time_since_epoch().count());

void solve() {
    string s;
    cin >> s;

    s = '#' + s;

    vector<int> dp(s.size());
    dp[0] = 1;

    map<char, int> last;

    for (int i = 1; i < s.size(); ++i) {
        dp[i] = 2 * dp[i-1];
        if (last.count(s[i])) {
            dp[i] -= dp[last[s[i]]-1];
        }
        last[s[i]] = i;
    }

    cout << dp.back() << "\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}


// a \oplus b = a + b - 2 (a & b)
