template <typename T>
struct SegmentTree {
    using Monoid = typename T::Monoid;
    int _n;
    std::vector<Monoid> _a;
    SegmentTree(int n) : SegmentTree(std::vector<Monoid>(n, T::id())) {}
    SegmentTree(const std::vector<Monoid> &a) : _n(std::bit_ceil(a.size())) {
        _a.assign(_n << 1, T::id());
        std::copy(a.begin(), a.end(), _a.begin() + _n);
        for (int i = _n - 1; i > 0; i--) {
            _a[i] = T::merge(_a[i << 1], _a[i << 1 | 1]);
        }
    }
    Monoid get(int l, int r) {
        l += _n, r += _n;
        Monoid res_l = T::id();
        Monoid res_r = T::id();
        while (l <= r) {
            if (l % 2 == 1) { res_l = T::merge(res_l, _a[l++]); }
            if (r % 2 == 0) { res_r = T::merge(_a[r--], res_r); }
            l >>= 1, r >>= 1;
        }
        return T::merge(res_l, res_r);
    }
    void set(int k, Monoid x) {
        k += _n;
        _a[k] = x;
        while (k >>= 1) {
            _a[k] = T::merge(_a[k << 1], _a[k << 1 | 1]);
        }
    }
    Monoid operator[](int k) const {
        return _a[k + _n];
    }
};
struct SegmentTreeNode {
    using Monoid = int;
    static constexpr Monoid id() {
        return 0;
    }
    static Monoid merge(const Monoid &x, const Monoid &y) {
        return x + y;
    }
};