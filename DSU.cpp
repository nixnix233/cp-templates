struct DSU {
    std::vector<int> id, sz;
    DSU() {}
    DSU(int n) {
        init(n);
    }
    void init(int n) {
        id.resize(n);
        std::iota(id.begin(), id.end(), 0);
        sz.assign(n, 1);
    }
    int find(int x) {
        if (id[x] != x) {
            id[x] = find(id[x]);
        }
        return id[x];
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        sz[x] += sz[y];
        id[y] = x;
        return true;
    }
    int size(int x) {
        return sz[find(x)];
    }
};
