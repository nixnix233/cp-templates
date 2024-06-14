template <int P>
struct Comb {
    int sz;
    std::vector<Z> fact, fact_inv;

    Comb() : sz{0}, fact{1}, fact_inv{1} {}
    Comb(int n) : Comb() {
        init(n);
    }
    
    void init(int n) {
        n = std::min(n, P);
        if (n <= sz) {
            return;
        }
        fact.resize(1 + n);
        fact_inv.resize(1 + n);
        
        for (int i = sz + 1; i <= n; i++) {
            fact[i] = fact[i - 1] * i;
        }
        fact_inv[n] = fact[n].inv();
        for (int i = n; i > sz; i--) {
            fact_inv[i - 1] = fact_inv[i] * i;
        }
        sz = n;
    }

    Z fac(int n) {
        if (n > sz) {
            init(2 * n);
        }
        return fact[n];
    }
    Z fac_inv(int n) {
        if (n > sz) {
            init(2 * n);
        }
        return fact_inv[n];
    }
    Z A(int n, int k) {
        if (n < k || k < 0) {
            return 0;
        }
        return fac(n) * fac_inv(k);
    }
    Z C(int n, int k) {
        if (n < k || k < 0) {
            return 0;
        }
        return fac(n) * fac_inv(k) * fac_inv(n - k);
    }
    Z H(int n, int k) {
        return C(n + k - 1, k);
    }
};
Comb<P> comb;