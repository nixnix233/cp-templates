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
    Monoid get(int k, int L, int R, int l, int r) {
        if (l == L && r == R) {
            return _a[k];
        }
        int mid = (L + R) >> 1;
        if (r <= mid) {
            return get(k << 1, L, mid, l, r);
        } else if (l >= mid + 1) {
            return get(k << 1 | 1, mid + 1, R, l, r);
        } else {
            return T::merge(get(k << 1, L, mid, l, mid), get(k << 1 | 1, mid + 1, R, mid + 1, r));
        }
    }
    void set(int k, int L, int R, int pos, Monoid x) {
        if (L == R) {
            _a[k] = x;
            return;
        }
        int mid = (L + R) >> 1;
        if (pos <= mid) {
            set(k << 1, L, mid, pos, x);
        } else {
            set(k << 1 | 1, mid + 1, R, pos, x);
        }
        _a[k] = T::merge(_a[k << 1], _a[k << 1 | 1]);
    }
    Monoid get(int l, int r) {
        return get(1, 1, _n, l + 1, r + 1);
    }
    void set(int pos, Monoid x) {
        set(1, 1, _n, pos + 1, x);
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