#include <bits/stdc++.h>
#include "lib/gen/gen_functions.h"

#define all(a) begin(a), end(a)
#define forn(i, n) for (int i = 0; i < n; ++i)

using namespace std;

string symbs = "a.AbB/";

char get_next_symb() {
    return symbs[getRnd(0, symbs.size() - 1)];
}

string ggget(int n) {
    string ret;
    while (n--) { 
        ret += (char) (getRnd(0, 3) + 'a');
    }
    return ret;
}

void gen_graph() {
    int n = getRnd(2, 15);
    int m = getRnd(3, 15);
    cout << n << " " << m << "\n";
    forn(i, m) {
        int u = getRnd(1, n - 1);
        int v = getRnd(u + 1, n);
        int w = getRnd(1, 10);
        cout << u << " " << v << " " << w << "\n";
    }
    int u = getRnd(1, n - 1);
    int v = getRnd(u + 1, n);
    cout << u << " " << v << "\n";
}

void gen_tree(int n) {
    for (int i = 2; i <= n; ++i) {
        cout << getRnd(1, i - 1) << " " << i << "\n";
    }
}

bool isPrime(int a) {
    if (a < 2) return false;
    for (int i = 2; i * i <= a; ++i) {
        if (a % i == 0) return false;
    }
    return true;
}

vector<int> g[100], revg[100];
int vis[100];
vector<int> tp;

void dfs(int u) {
    vis[u] = 1;
    for (int v : g[u]) {
        if (!vis[v]) {
            dfs(v);
        }
    }
    tp.push_back(u);    
}

int main() {
    // cout << 1 << "\n";
    // int n = getRnd(4, 7);
    // int m = getRnd(4, 7);
    // cout << n << " " << m << "\n";
    // vector<int> dx = {-1, -1, -1, 0, 0, 1, 1, 1};
    // vector<int> dy = {-1, 0, 1, -1, 1, -1, 0, 1};
    // vector<string> a(n);
    // forn(i, n) a[i].assign(m, '.');
    // forn(i, n) {
    //     forn(j, m) {
    //         bool ok = false;

    //         forn(k, 8) {
    //             int x = i + dx[k];
    //             int y = j + dy[k];
    //             if (0<=x && 0<=y && x < n && y < m && a[x][y] == 'X') ok = true;
    //         }

    //         if (!ok) {
    //             if (getRnd(1, 3) == 1) {
    //                 a[i][j] = 'X';
    //             }
    //         }
    //     }
    // }
    // forn(i, n) cout << a[i] << "\n";
    cout << getRnd(1, 100) << " " << getRnd(1, 100) << "\n";
    return 0;
}


