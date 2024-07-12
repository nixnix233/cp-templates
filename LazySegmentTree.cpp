template <class S, S (*op)(S, S), S (*e)(), class T, T (*composition)(T, T), T (*id)(), S (*mapping)(T, S)>
struct LazySegmentTree {
    std::vector<S> a_;
    std::vector<T> tag_;
    int n_, offset_, lg_;
    LazySegmentTree(int n) : LazySegmentTree(std::vector<S>(1 + n, e())) {}
    LazySegmentTree(const std::vector<S> &a) : n_{(int)a.size() - 1} {
        int sz = bitceil(n_);
        a_.assign(sz * 2, e());
        tag_.assign(sz * 2, id());
        offset_ = sz - 1;
        lg_ = std::__lg(sz);
        for (int i = 1; i <= n_; i++) {
            a_[i + offset_] = a[i];
        }
        for (int i = sz - 1; i >= 1; i--) {
            update(i);
        }
    }
    S get(int k) {
        k += offset_;
        for (int i = lg_; i >= 1; i--) {
            push(k >> i);
        }
        return a_[k];
    }
    S get(int l, int r) {
        l += offset_;
        r += offset_;
        for (int i = lg_; i >= 1; i--) {
            if (bitcut(l, i) != l) { push(l >> i); }
            if (bitcut(r + 1, i) != r + 1) { push(r >> i); }
        }
        S ans_l = e(), ans_r = e();
        while (l <= r) {
            if ((l & 1) == 1) { ans_l = op(ans_l, a_[l++]); }
            if ((r & 1) == 0) { ans_r = op(a_[r--], ans_r); }
            l >>= 1;
            r >>= 1;
        }
        return op(ans_l, ans_r);
    }
    S get_all() {
        return a_[1];
    }
    void set(int k, S val) {
        k += offset_;
        for (int i = lg_; i >= 1; i--) {
            push(k >> i);
        }
        a_[k] = val;
        for (int i = 1; i <= lg_; i++) {
            update(k >> i);
        }
    }
    void apply(int k, T f) {
        k += offset_;
        for (int i = lg_; i >= 1; i--) {
            push(k >> i);
        }
        a_[k] = mapping(f, a_[k]);
        for (int i = 1; i <= lg_; i++) {
            update(k >> i);
        }
    }
    void apply(int l, int r, T f) {
        l += offset_;
        r += offset_;
        for (int i = lg_; i >= 1; i--) {
            if (bitcut(l, i) != l) { push(l >> i); }
            if (bitcut(r + 1, i) != r + 1) { push(r >> i); }
        }
        [&](int l, int r) {
            while (l <= r) {
                if ((l & 1) == 1) { apply_node(l++, f); }
                if ((r & 1) == 0) { apply_node(r--, f); }
                l >>= 1;
                r >>= 1;
            }
        }(l, r);
        for (int i = 1; i <= lg_; i++) {
            if (bitcut(l, i) != l) { update(l >> i); }
            if (bitcut(r + 1, i) != r + 1) { update(r >> i); }
        }
    }
    template <class F> int max_right(int l, F pred) {
        l += offset_;
        for (int i = lg_; i >= 1; i--) { push(l >> i); }
        assert(pred(a_[l]));
        S cur = e();
        do {
            while ((l & 1) == 0) { l >>= 1; }
            if (pred(op(cur, a_[l]))) {
                cur = op(cur, a_[l]);
                l++;
            } else {
                while (l * 2 <= n_ + offset_) {
                    push(l);
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
        r += offset_;
        for (int i = lg_; i >= 1; i--) { push(r >> i); }
        assert(pred(a_[r]));
        S cur = e();
        do {
            while (r > 1 && (r & 1) == 1) { r >>= 1; }
            if (pred(op(a_[r], cur))) {
                cur = op(a_[r], cur);
                r--;
            } else {
                while (r * 2 + 1 <= n_ + offset_) {
                    push(r);
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
    void apply_node(int k, T f) {
        a_[k] = mapping(f, a_[k]);
        if (k <= offset_) {
            tag_[k] = composition(f, tag_[k]);
        }
    }
    void push(int k) {
        apply_node(k << 1, tag_[k]);
        apply_node((k << 1) | 1, tag_[k]);
        tag_[k] = id();
    }
    int bitcut(int n, int len) {
        return (n >> len) << len;
    }
    int bitceil(int n) {
        int ans = 1;
        while (ans < n) {
            ans <<= 1;
        }
        return ans;
    }
};
