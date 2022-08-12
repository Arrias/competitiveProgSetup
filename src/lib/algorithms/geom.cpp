#define double long double

struct pt {
    int x, y, num;
    int len() {
        return x * x + y * y;
    }
};

int operator*(pt a, pt b) {
    return a.x * b.y - b.x * a.y;
}

int quad(pt a) {
   return ((a.x>=0)^(a.y>=0))|((a.y>=0)<<1);
}

bool operator<(pt a, pt b) {
    if (quad(a) != quad(b)) return quad(a) < quad(b);
    if (a*b == 0) return a.len() < b.len();
    return a * b > 0;
}

double M_PI = acos(-1);
double angle(double x, double y, double c, double d) {
    double a, b, e;
    b = atan2(d, c);
    if (b < 0) b += 2 * M_PI;
    a = atan2(y, x);
    if (a < 0) a += 2 * M_PI;
    e = fabs(a - b);
    if (e > M_PI) e = 2 * M_PI - e; 
    return e;
}