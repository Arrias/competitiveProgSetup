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
#include <functional>
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

struct segments {
    set<pair<int, int>> good;
    set<pair<int, int>> bad;

    int soch(pair<int, int> a, pair<int, int> b) {
        return max(0ll, min(a.second, b.second) - max(a.first, b.first) + 1ll);
    }

    void add(int l, int r) {
        // debug(l);
        // debug(r);
        auto it = good.upper_bound({l, -1});
        if (it != good.begin()) {
            --it;
            // debug(*it);
            // debug(soch(*it, {l, r}));
            if (soch(*it, {l, r}) == r - l + 1) {
                bad.insert(*it);
                good.erase(it);
                good.insert({l, r});
            }
            else if (!soch(*it, {l, r})) {
                good.insert({l, r});
            }
        } else {
            good.insert({l, r});
        }
       // debr(all(good));
    }

    void rem(int l, int r) {
        if (bad.find({l, r}) != bad.end()) {
            bad.erase({l, r});
            return;
        }
        good.erase({l, r});
        auto it = bad.upper_bound({l, -1});
        if (it != bad.begin()) {
            --it;
            auto puff = good.insert(*it).first;
            bool ok = true;
            if (puff != good.begin()) ok &= !soch(*prev(puff), *puff);
            if (next(puff) != good.end()) ok &= !soch(*next(puff), *puff);
            if (ok) bad.erase(it);
            else good.erase(puff);
        }
    }
};

void solve() {
    int n;
    cin >> n;
    
    vector<vector<int>> g1(n), g2(n);
    for (int i = 1; i < n; ++i) {
        int p1;
        cin >> p1;
        --p1;
        g1[p1].push_back(i);
    }

    for (int i = 1; i < n; ++i) {
        int p2;
        cin >> p2;
        --p2;
        g2[p2].push_back(i);
    }

    vector<int> tin(n), tout(n);
    int tms = 0;

    function<void(int)> dfs = [&] (int u) {
        tin[u] = tms++;
        for (int v : g2[u]) {
            dfs(v);
        }
        tout[u] = tms++;
    };

    dfs(0);

    int res = 0;
    segments sg;

    function<void(int)> calc = [&] (int u) {
        sg.add(tin[u], tout[u]);
        res = max(res, (int)sg.good.size());

        for (int v : g1[u]) {
            calc(v);
        }

        sg.rem(tin[u], tout[u]);
    };
    calc(0);

    cout << res << "\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}