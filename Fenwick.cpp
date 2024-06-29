template <typename T>
struct Fenwick {
    int n;
    std::vector<T> a;
    Fenwick(int n) : n{n} {
        a.assign(1 + n, T{});
    }
    void add(int k, int x) {
        for (int i = k; i <= n; i += i & -i) {
            a[i] += x;
        }
    }
    T sum(int k) {
        T ans{};
        for (int i = k; i > 0; i -= i & -i) {
            ans += a[i];
        }
        return ans;
    }
    T sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
    int kth(T x) {
        int p = 0;
        T cur{};
        for (int len = 1 << std::__lg(n); len; len /= 2) {
            if (p + len <= n && cur + a[p + len] < x) {
                cur += a[p + len];
                p += len;
            }
        }
        return 1 + p;
    }
};
