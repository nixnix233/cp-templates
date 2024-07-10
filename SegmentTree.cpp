template <class T, T (*op)(T, T), T (*e)()>
struct SegmentTree {
    std::vector<T> a_;
    int n_, offset_;
    SegmentTree(int n) : SegmentTree(std::vector<T>(1 + n, e())) {}
    SegmentTree(const std::vector<T> &a) : n_{(int)a.size() - 1} {
        int sz = bitceil(n_);
        a_.assign(sz * 2, e());
        offset_ = sz - 1;
        for (int i = 1; i <= n_; i++) {
            a_[i + offset_] = a[i];
        }
        for (int i = sz - 1; i >= 1; i--) {
            update(i);
        }
    }
    T get(int k) {
        return a_[k + offset_];
    }
    T get(int l, int r) {
        T ans_l = e(), ans_r = e();
        l += offset_;
        r += offset_;
        while (l <= r) {
            if ((l & 1) == 1) { ans_l = op(ans_l, a_[l++]); }
            if ((r & 1) == 0) { ans_r = op(a_[r--], ans_r); }
            l >>= 1;
            r >>= 1;
        }
        return op(ans_l, ans_r);
    }
    T get_all() {
        return a_[1];
    }
    void set(int k, T val) {
        k += offset_;
        a_[k] = val;
        k >>= 1;
        while (k >= 1) {
            update(k);
            k >>= 1;
        }
    }
    template <class F> int max_right(int l, F pred) {
        assert(pred(a_[l + offset_]));
        T cur = e();
        l += offset_;
        do {
            while ((l & 1) == 0) { l >>= 1; }
            if (pred(op(cur, a_[l]))) {
                cur = op(cur, a_[l]);
                l++;
            } else {
                while (l * 2 <= n_ + offset_) {
                    l <<= 1;
                    if (pred(op(cur, a_[l]))) {
                        cur = op(cur, a_[l]);
                        l++;
                    }
                }
                return l - 1 - offset_;
            }
        } while ((l & -l) != l);
        return n_;
    }
    template <class F> int min_left(int r, F pred) {
        assert(pred(a_[r + offset_]));
        T cur = e();
        r += offset_;
        do {
            while (r > 1 && (r & 1) == 1) { r >>= 1; }
            if (pred(op(a_[r], cur))) {
                cur = op(a_[r], cur);
                r--;
            } else {
                while (r * 2 + 1 <= n_ + offset_) {
                    r = (r << 1) | 1;
                    if (pred(op(a_[r], cur))) {
                        cur = op(a_[r], cur);
                        r--;
                    }
                }
                return r + 1 - offset_;
            }
        } while (((r + 1) & -(r + 1)) != r + 1);
        return 1;
    }
    void update(int k) {
        a_[k] = op(a_[k << 1], a_[(k << 1) | 1]);
    }
    int bitceil(int n) {
        int ans = 1;
        while (ans < n) {
            ans <<= 1;
        }
        return ans;
    }
};
