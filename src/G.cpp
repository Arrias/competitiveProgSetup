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
#include <map>
#include <climits>
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

template<typename T, class F = function<T(const T &, const T &)>>
class SparseTable {
public:
    int n, l;
    vector<vector<T>> mat;
    vector<T> data;
    vector<int> logs;
    F func;

    SparseTable(const vector<T> &a, const F &f) : func(f), data(a) {
        n = a.size();
        l = 25; // max_log
        logs.resize(n + 2);
        for (int i = 2; i < n + 2; ++i)
            logs[i] = logs[i / 2] + 1;
        mat.assign(l, vector<int>(n, 0));
        iota(mat[0].begin(), mat[0].end(), 0);
        for (int i = 1; i < l; ++i) {
            for (int j = 0; j < n; ++j) {
                if (j + (1 << (i - 1)) >= n) break;
                T c = func(a[mat[i - 1][j]], a[mat[i - 1][j + (1 << (i - 1))]]);
                mat[i][j] = ((c == a[mat[i - 1][j]]) ? mat[i - 1][j] : mat[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    int getId(int l, int r) {
        int c = logs[r - l + 1];
        r++;
        T val = func(data[mat[c][l]], data[mat[c][r - (1 << c)]]);
        return ((val == data[mat[c][l]]) ? mat[c][l] : mat[c][r - (1 << c)]);
    }

    T getVal(int l, int r) {
        return data[getId(l, r)];
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> a(n - 1);
    forn(i, n - 1) {
        cin >> a[i];
        --a[i];
    }
    a.push_back(n);
    vector<int> dp(n);

    SparseTable<int> sp(a, [](int i, int j) {return max(i, j);});

    dp[n - 2] = 1;
    int res = 1;

    for (int i = n - 3; i >= 0; --i) {
        int nxt = sp.getId(i, a[i]);

        //debug(nxt);
        dp[i] += dp[nxt];
        dp[i] += a[nxt] - a[i] - 1;
        dp[i] += nxt - i;
        dp[i] += n - a[nxt];
        res += dp[i];
    }

    cout << res << "\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
