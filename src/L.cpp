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
using ld = long double;

mt19937_64 rnd(std::chrono::system_clock::now().time_since_epoch().count());

vector<pair<int, int>> factor(int n) {
    vector<pair<int, int>> result;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            result.emplace_back(i, 0);
            while (n % i == 0) {
                n /= i;
                result.back().second++;
            }
        }
    }
    if (n > 1) {
        result.emplace_back(n, 1);
    }
    return result;
}

int calc_phi(int n) {
    int result = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0) {
                n /= i;
            }
            result -= result / i;
        }
    }
    if (n > 1) {
        result -= result / n;
    }
    return result;
}

int b_pow(int a, int b, int mod) {
    if (b == 0) {
        return 1;
    }
    if (b & 1) {
        return (static_cast<int>(b_pow(a, b - 1, mod)) * static_cast<int>(a)) % mod;
    }
    int c = b_pow(a, b / 2, mod);
    return (c * c) % mod;
}

bool check(int n) {
    if (n == 1 || n == 2 || n == 4) {
        return true;
    }
    auto factorization = factor(n);
    if (factorization.size() == 1) {
        return (factorization[0].first % 2 == 1);
    }
    if (factorization.size() == 2) {
        return factorization[0] == make_pair(2ll, 1ll) ||
        factorization[1] == make_pair(2ll, 1ll);
    }
    return false;
}

int get(int mod) {
    if (!check(mod)) {
        return -1;
    }
    int phi = calc_phi(mod);
    auto f = factor(phi);
    for (int root = 1; root <= mod; root++) {
        if (gcd(root, mod) != 1) {
            continue;
        }
        bool ok = true;
        for (auto [x, _] : f) {
            ok &= b_pow(root, phi / x, mod) != 1;
        }
        if (ok) {
            return root;
        }
    }
    assert(false);
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0); 

    // vector<int> a(9);
    // iota(all(a), 1);

    // do {
    //     int p = 1;
    //     set<int> st;
    //     for (int i : a) {
    //         p *= i;
    //         p %= 9;
    //         st.insert(p);
    //     }
    //     if (st.size() == 9) {
    //         cout << "YES\n";
    //         for (int i : a) cout << i << "\n";
    //         return 0;
    //     }
    // } while (next_permutation(all(a)));
    int n;
    cin >> n;

    if (n == 1) {
        cout << "YES\n1\n";
        return 0;
    }
    if (n == 2) {
        cout << "YES\n1\n2\n";
        return 0;
    }
    if (n == 4) {
        cout << "YES\n1\n3\n2\n4\n";
        return 0;
    }

    bool isPrime = true;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            isPrime = false;
        }
    }
    if (!isPrime) {
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";

    int root = get(n);
    if (root == -1) {
        cout << "NO\n";
        return 0;
    }

    debug(root);
    int l = 0, r = n - 2;
    bool step = false;
    int pr = 1;

    while (l <= r) {
        int nx = -1;
        if (!step) {
            nx = b_pow(root, l++, n);
        } else {
            nx = b_pow(root, r--, n);
        }
        //cout << nx << "\n";
        cout << (nx * b_pow(pr, n - 2, n)) % n << "\n";
        step ^= 1;
        pr = nx;
    }
    cout << n << "\n";

    return 0;
}
