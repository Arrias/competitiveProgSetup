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
#include <cstring>
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

const int N = 4e5 + 50;
int sz[N], n;
vector<int> g[N];
int ans[N];

int calc_sz(int u, int p) {
    sz[u] = 1;
    for (int v : g[u]) {
        if (v == p) continue;
        sz[u] += calc_sz(v, u);
    }
    return sz[u];
}

int find_centroid(int u, int p) {
    for (int v : g[u]) {
        if (v == p) continue;
        if (sz[v] > n / 2) {
            return find_centroid(v, u);
        }
    }
    return u;
}

vector<int> get_sizes(int u, int p) {
    sz[u] = 1;
    vector<int> ret;
    for (int v : g[u]) {
        if (v == p) continue;
        auto x = get_sizes(v, u);
        sz[u] += sz[v];
        if (x.size() > ret.size()) swap(x, ret);
        for (int i : x) ret.push_back(i);
    }
    ret.push_back(sz[u]);
    return ret;
}

multiset<int> ms;
void calc_anses(int u, int top, int p) {
    debug(u);
    debug(top);
    int diff = top - n / 2;
    auto it = ms.lower_bound(diff);
    ans[u] = (it != ms.end() && *it <= n / 2);
    top++;
    for (int v : g[u]) {
        if (v == p) continue;
        top += sz[v];
    }
    for (int v : g[u]) {
        if (v == p) continue;
        top -= sz[v];
        calc_anses(v, top, u);
        top += sz[v];
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    forn(i, n - 1) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    assert(calc_sz(0, -1) == n);
    int c = find_centroid(0, -1);
    ans[c] = 1;

    vector<vector<int>> szs;
    int top = 1;

    for (int v : g[c]) {
        szs.push_back(get_sizes(v, c));
        for (auto i : szs.back()) ms.insert(i);
        top += sz[v];
    }

    debug(c + 1);
    debug(top);
    for (auto i : szs) {
        debr(all(i));
    }

    int predator = 0;
    for (int v : g[c]) {
        top -= sz[v];     
        for (int i : szs[predator]) ms.erase(ms.find(i));

        ms.insert(top);
        
        calc_anses(v, top, c);
        for (int i : szs[predator]) ms.insert(i);

        ms.erase(ms.find(top));
        top += sz[v];

        predator++;
    }
    
    forn(i, n) cout << ans[i] << " ";
    cout << "\n";

    return 0;
}
