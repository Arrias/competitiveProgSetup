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
#define forn(i, n) for (int i = 0; i < n; ++i)
#define all(a) begin(a), end(a)
//#define int long long
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
    int n, m;
    cin >> n >> m;
    vector<string> a(n);
    
    forn(i, n) {
        cin >> a[i];
    }

    if (n == 1 || m == 1) {
        forn(i, n) forn(j, m) a[i][j] = 'X';
        forn(i, n) cout << a[i] << "\n";
        return;
    }   

    for (int i = 0; i < n; i += 3) {
        forn(j, m) a[i][j] = 'X';
        if (i + 3 < n) {
            bool ok = false;
            forn(j, m) {
                if (ok) break;
                if (a[i+1][j] == 'X') {
                    a[i+2][j] = 'X';
                    ok = 1;
                }  
                if (a[i+2][j] == 'X') {
                    a[i+1][j] = 'X';
                    ok = 1;
                }
            }
            if (!ok) a[i+1][0] = a[i+2][0] = 'X';
        }
    }   

    if (n % 3 == 0) {
        forn(j, m) {
            if (a[n-1][j] == 'X') {
                a[n-2][j] = 'X';
            }
        }
    }

    forn(i, n) {
        cout << a[i] << "\n";
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.setf(ios::fixed);
    cout.precision(10);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

