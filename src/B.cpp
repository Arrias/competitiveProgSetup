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
#include <bitset>
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

mt19937_64 rnd(std::chrono::system_clock::now().time_since_epoch().count());
   
void solve() {
    int n;
    cin >> n;
    cout << n << "\n";
    vector<int> a(n);
    iota(all(a), 1);
    forn(i, n) cout << a[i] << " "; cout << "\n";
    swap(a[n-1], a[n-2]);
    forn(i, n) cout << a[i] << " "; cout << "\n";
    int pos = n - 2;
    while (pos - 1 >= 0) {
        swap(a[pos-1],a[pos]);
        forn(i, n) cout << a[i] << " ";
        cout << "\n";
        pos--;
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);         
    cout.setf(ios::fixed);
    cout.precision(10); 

    map<int, int> z;
    for (auto [x, y] : z) {

    }
    return 0;
}