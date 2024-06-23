template <typename T>
struct Fenwick {
    int n;
    std::vector<T> a;
    Fenwick(int n) : n{n} {
        a.assign(n, T{});
    }
    void add(int k, int x) {
        k++;
        for (int i = k; i <= n; i += i & -i) {
            a[i - 1] += x;
        }
    }
    T sum(int k) {
        T ans{};
        for (int i = k; i > 0; i -= i & -i) {
            ans += a[i - 1];
        }
        return ans;
    }
    T sum(int l, int r) {
        return sum(r) - sum(l);
    }
    int kth(T x) {
        int k = 0;
        T cur{};
        for (int len = 1 << std::__lg(n); len; len /= 2) {
            if (k + len <= n && cur + a[k + len - 1] <= x) {
                cur += a[k + len - 1];
                k += len;
            }
        }
        return k;
    }
};
