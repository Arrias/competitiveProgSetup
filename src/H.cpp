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
#define double long double
#define sqr(x) ((x) * (x))

#ifndef _debug
#define debug(...) 42
#define debr(...) 42
#else
#define debug(x) cout << #x << " = " << x << endl
#define debr(...) { cout << #__VA_ARGS__ << " = ";  _debr(VA_ARGS); }
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
const int m2 = 1e9 + 6;

using ModInt = Mint<m1>;
using Momo = Mint<m2>;

template<class T>
class matrix {
private:
    vector<vector<T>> data;
public:
    int n{}, m{};

    matrix() = default;

    matrix(int nn, int mm) {
        n = nn;
        m = mm;
        data.assign(n, vector<T>(m, 0));
    }

    void init(int nn, int mm) {
        n = nn;
        m = mm;
        data.assign(n, vector<T>(m, 0));
    }

    T &operator()(int i, int j) {
        return data[i][j];
    }

    const T &operator()(int i, int j) const {
        return data[i][j];
    }

    void print() {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cout << data[i][j] << " ";
            }
            cout << "\n";
        }
    }
};

template<class T>
matrix<T> operator*(matrix<T> a, matrix<T> b) {
    matrix<T> c(a.n, b.m);
    for (int i = 0; i < a.n; ++i) {
        for (int j = 0; j < b.m; ++j) {
            for (int k = 0; k < b.n; ++k) {
                c(i, j) += a(i, k) * b(k, j);
            }
        }
    }
    return c;
}

template<class T>
matrix<T> pow(matrix<T> a, int k) {
    if (k == 0) {
        matrix<T> ret(a.n, a.m);
        forn(i, a.n) ret(i, i) = 1;
        return ret;
    }
    auto half = pow(a, k / 2);
    half = half * half;
    if (k % 2) half = half * a;
    return half;
}

using mmatrix = matrix<Momo>;

int get_k(int n) {
    mmatrix kmaxtrix(5, 1);
    kmaxtrix(3, 0) = 4;
    kmaxtrix(4, 0) = 1;   

    mmatrix step(5, 5);
    step(0, 1) = 1;
    step(1, 2) = 1;
    
    step(2, 0) = step(2, 1) = step(2, 2) = 1;
    step(2, 3) = 2;
    step(2, 4) = m2 - 6;

    step(3, 3) = step(3, 4) = 1;
    step(4, 4) = 1;

    int deg = n - 4 + 1;
    return (pow(step, deg) * kmaxtrix)(2, 0).value;
}

// pos \in {0, 1, 2}
int get(int pos, int n) {
    mmatrix kmaxtrix(3, 1);
    kmaxtrix(pos, 0) = 1;

    mmatrix step(3, 3);
    step(0, 1) = 1;
    step(1, 2) = 1;
    step(2, 0) = step(2, 1) = step(2, 2) = 1;

    int deg = n - 4 + 1;
    return (pow(step, deg) * kmaxtrix)(2, 0).value;
}

void solve() {
    int n, f1, f2, f3, c;
    cin >> n >> f1 >> f2 >> f3 >> c;

    int k = get_k(n);
    int r_1 = get(0, n);
    int r_2 = get(1, n);
    int r_3 = get(2, n);

    ModInt res = ModInt(c) ^ k;
    res *= ModInt(f1) ^ r_1;
    res *= ModInt(f2) ^ r_2;
    res *= ModInt(f3) ^ r_3;

    cout << res << "\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cout.setf(ios::fixed);
    cout.precision(10);
    solve();
    
    return 0;
}
