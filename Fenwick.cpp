template <typename T>
struct Fenwick {
    int n;
    std::vector<T> a;
    Fenwick(int n) : n{1 + n} {
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
};
