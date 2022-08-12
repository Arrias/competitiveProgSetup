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
#include <deque>
#include <chrono>
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

void hui(string s) {
    cout << s << "\n";
    exit(0);
}

map<pair<int, int>, int> color;
int n, m;
vector<string> a;

void dfs(int i, int j, int predi = -1, int predj = -1) {
    //cout << i << " " << j << "\n";
    if (i < 0 || j < 0 || i >= n || j >= m) return;
    if (a[i][j] != 'X') return;
    if (color[{i, j}] == 2) return;
    if (color[{i, j}] == 1) {
        cout << 0 << "\n";
        exit(0);
    }
    color[{i,j}] = 1;
    if (!(i-1 == predi && j == predj)) dfs(i-1, j, i, j);
    if (!(i+1 == predi && j == predj)) dfs(i+1, j, i, j);
    if (!(i == predi && j - 1 == predj)) dfs(i, j-1, i, j);
    if (!(i == predi && j + 1 == predj)) dfs(i, j+1, i, j);
    color[{i,j}] = 2;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> n >> m;
    a.resize(n);
    forn(i, n) cin >> a[i];

    forn(i, n) {
        cin >> a[i];
    }

    forn(i, n - 1) {
        forn(j, m - 1) {
            if (a[i][j] == 'X' && !color.count({i, j})) {
                dfs(i, j);
            }
        }
    }
    cout << 1 << "\n";
    return 0;
}