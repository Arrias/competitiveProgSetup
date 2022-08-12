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

const int INF = 2e9;
const int N = 305;
const int NOPE = -2;

int g[N][N];
int n;
int a[N], b[N];
int match[N];
int pleft[N];
int pright[N];

pair<int, int> new_edges[N];
int new_edges_cnt;
int min_pos[N];
int min_delta[N];

void solve() {
    cin >> n;

    forn(i, n) {
        forn(j, n) {
            cin >> g[i][j];
        }
    }

    fill(match, match + n, NOPE);

    forn(i, n) {
        fill(pleft, pleft + n, NOPE);
        fill(pright, pright + n, NOPE);
        fill(min_pos, min_pos + n, NOPE);
        fill(min_delta, min_delta + n, INF);

        auto add_cell = [&] (int i, int j) {
            int curd = g[i][j] - a[i] - b[j];
            if (min_delta[j] > curd) {
                min_delta[j] = curd;
                min_pos[j] = i;
            }
        };

        auto add_row = [&] (int i) {
            forn(j, n) {
                add_cell(i, j);
            }
        };

        pright[i] = -1;
        add_row(i);

        function<bool(int, int)> add_edge = [&] (int from, int to) {
            if (match[to] == NOPE) {
                match[to] = from;
                int z = from;
                while (z != i) {
                    int v = pleft[pright[z]];
                    match[pright[z]] = v;
                    z = v;
                }
                return true;
            }  
            if (pright[match[to]] != NOPE) return false;
            pleft[to] = from;
            pright[match[to]] = to;
            add_row(match[to]);
            return false;
        };

        bool ok = false;
        while (!ok) {
            int min_col = -1;

            forn(j, n) {
                if (pleft[j] == NOPE) {
                    if (min_col == -1 || min_delta[min_col] > min_delta[j]) {
                        min_col = j;
                    }
                }
            }

            int mind = min_delta[min_col];
            forn(j, n) {
                if (pright[j] == NOPE) {
                    a[j] -= mind;
                }
                if (pleft[j] == NOPE) {
                    b[j] += mind;
                    min_delta[j] -= mind;
                }
            }   

            ok |= add_edge(min_pos[min_col], min_col);
        }
    }

    int res = 0;
    forn(i, n) {
        assert(match[i] != NOPE);
        res += g[match[i]][i];
    }

    cout << res << "\n";
    forn(i, n) {
        cout << match[i] + 1 << " " << i + 1 << "\n";
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}