struct DSU {
    std::vector<int> id, sz;
    int n;
    DSU(int n) : n{n} {
        id.resize(n);
        sz.resize(n);
        std::iota(id.begin(), id.end(), 0);
        std::fill(sz.begin(), sz.end(), 1);
    }
    int find(int x) {
        if (id[x] != x) {
            id[x] = find(id[x]);
        }
        return id[x];
    }
    int size(int x) {
        return sz[find(x)];
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    bool merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) {
            return false;
        }
        sz[x] += sz[y];
        id[y] = x;
        return true;
    }
};
