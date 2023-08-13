template <typename T>
struct Fenwick {
    int _n;
    std::vector<T> _a;
    Fenwick(int n) : _n(n), _a(n) {}
    void add(int k, T c) {
        for (int i = k + 1; i <= _n; i += i & -i) {
            _a[i - 1] += c;
        }
    }
    T sum(int k) {
        T ans = 0;
        for (int i = k + 1; i > 0; i -= i & -i) {
            ans += _a[i - 1];
        }
        return ans;
    }
    T sum(int l, int r) {
        return l == 0 ? sum(r) : sum(r) - sum(l - 1);
    }
};