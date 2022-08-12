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
#include <cstring>
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

template<int mod>
struct Mint {
    int value;

    Mint(int value = 0) : value(value) {}

    Mint operator+(Mint b) {
        Mint ret(*this);
        ret.value += b.value;
        if (ret.value >= mod) ret.value -= mod;
        return ret;
    }

    Mint operator-(Mint b) {
        Mint ret(*this);
        ret.value -= b.value;
        if (ret.value < 0) ret.value += mod;
        return ret;
    }

    Mint operator*(Mint b) {
        Mint ret(*this);
        ret.value = (1ll * ret.value * b.value) % mod;
        return ret;
    }

    Mint operator^(int k) {
        if (k == 0) return 1;
        auto ret = *this ^ (k / 2);
        ret *= ret;
        if (k & 1) ret *= *this;
        return ret;
    }

    Mint operator/(Mint b) {
        auto ret(*this);
        ret = ret * (b ^ (mod - 2));
        return ret;
    }

    void operator+=(Mint b) { *this = *this + b; }

    void operator-=(Mint b) { *this = *this - b; }

    void operator*=(Mint b) { *this = *this * b; }

    void operator/=(Mint b) { *this = *this / b; }
};

template<int mod>
ostream &operator<<(ostream &out, const Mint<mod> &v) {
    out << v.value;
    return out;
}

template<int mod>
istream &operator>>(istream &in, Mint<mod> &v) {
    in >> v.value;
    return in;
}

template<int mod>
struct Combinator {
    void extgcd(ll a, ll b, ll &x0, ll &y0) {
        if (b == 0) {
            x0 = 1, y0 = 0;
            return;
        }
        ll xs, ys;
        extgcd(b, a % b, xs, ys);
        x0 = ys;
        y0 = xs - ys * (a / b);
    }

    vector<Mint<mod>> degrees(Mint<mod> k, int sz) {
        vector<Mint<mod>> ret(sz);
        ret[0] = 1;
        for (int i = 1; i < sz; ++i) {
            ret[i] = (ret[i - 1] * k);
        }
        return ret;
    }

    Mint<mod> fact(int n) {
        static vector<Mint<mod>> vec(1, Mint<mod>(1));
        while (n >= (int) vec.size()) {
            vec.push_back(vec.back() * Mint<mod>(vec.size()));
        }
        return vec[n];
    }

    Mint<mod> inv_fact(int n) {
        static vector<Mint<mod>> vec(1, Mint<mod>(1));
        while (n >= (int) vec.size()) {
            vec.push_back(vec.back() / Mint<mod>(vec.size()));
        }
        return vec[n];
    }

    Mint<mod> binom(int n, int r) {
        if (n < r) return 0;
        return fact(n) * inv_fact(n - r) * inv_fact(r);
    }

    Mint<mod> on_terms(int n, int r) {
        return binom(n + r - 1, r - 1);
    }
};

const int m1 = 1e9 + 7;
using ModInt = Mint<m1>;
Combinator<m1> K;

ModInt cnt(int a, int b) {
    ModInt ret = 0; 

    for (int cnt = 1; cnt <= min(a, b); ++cnt) {
        ret += K.binom(a - 1, cnt - 1) * K.binom(b, cnt);
    }
    return ret;
}   

ModInt cnt2(int a, int b) {
    if (b == 0) return 0;
    return K.binom(a + b - 1, b - 1);
}

ModInt f(int a) {
    ModInt ret = 0;
    for (int i = 1; i <= a; ++i) {
        ret += K.binom(a, i) * K.binom(a, i);
    }
    return ret;
}

void solve() {
    string s;
    cin >> s;

    int opened = 0;
    int closed = 0;
    for (char c : s) closed += c == ')';

    ModInt res = 0;
    for (char c : s) {
        closed -= (c == ')');
        opened += (c == '(');
        if (c == '(') {
            res += cnt2(opened, closed);
        }
    }   

    cout << res << "\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);     

    solve();

    return 0;
}