const int P = 1E9 + 7;

template <int P>
struct Zn {
    int x;
    Zn() : x{0} {}
    Zn(i64 x) : x{norm(x)} {}

    int norm(i64 val) {
        return (val % P + P) % P;
    }
    Zn inv() {
        return power(*this, P - 2);
    }
    friend Zn power(Zn a, i64 b) {
        int ans = 1, x = a.x;
        for (; b > 0; b /= 2) {
            if (b % 2 == 1) {
                ans = 1LL * ans * x % P;
            }
            x = 1LL * x * x % P;
        }
        return Zn{ans};
    }
    
    Zn& operator+=(Zn rhs)  {
        x = norm(1LL * x + rhs.x);
        return *this;
    }
    Zn& operator-=(Zn rhs) {
        x = norm(1LL * x - rhs.x);
        return *this;
    }
    Zn& operator*=(Zn rhs) {
        x = norm(1LL * x * rhs.x);
        return *this;
    }
    Zn& operator/=(Zn rhs) {
        *this *= rhs.inv();
        return *this;
    }

    Zn operator-() {
        return Zn{P - x};
    }
    friend Zn operator+(Zn lhs, Zn rhs) {
        return lhs += rhs;
    }
    friend Zn operator-(Zn lhs, Zn rhs) {
        return lhs -= rhs;
    }
    friend Zn operator*(Zn lhs, Zn rhs) {
        return lhs *= rhs;
    }
    friend Zn operator/(Zn lhs, Zn rhs) {
        return lhs /= rhs;
    }

    friend bool operator==(Zn lhs, Zn rhs) {
        return lhs.x == rhs.x;
    }
    friend bool operator!=(Zn lhs, Zn rhs) {
        return lhs.x != rhs.x;
    }
    friend bool operator<(Zn lhs, Zn rhs) {
        return lhs.x < rhs.x;
    }

    friend std::istream& operator>>(std::istream& in, Zn& a) {
        i64 val;
        in >> val;
        a = Zn{val};
        return in;
    }
    friend std::ostream& operator<<(std::ostream& out, const Zn& a) {
        return out << a.x;
    }
};
using Z = Zn<P>;
