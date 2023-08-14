template <typename T>
struct SegmentTree {
	using Monoid = typename T::Monoid;
	int _p2;
	std::vector<Monoid> _a;
	SegmentTree(int n) : SegmentTree(std::vector<Monoid>(n, T::id())) {}
	SegmentTree(const std::vector<Monoid> &a) : _p2(std::bit_ceil(a.size())) {
		_a.assign(_p2 * 2, T::id());
		std::copy(a.begin(), a.end(), _a.begin() + _p2);
		for (int i = _p2 - 1; i > 0; i--) {
			_a[i] = T::merge(_a[i * 2], _a[i * 2 + 1]);
		}
	}
	Monoid get(int l, int r) {
		l += _p2, r += _p2;
		Monoid res = T::id();
		while (l <= r) {
			if (l % 2 == 1) { res = T::merge(res, _a[l++]); }	
			if (r % 2 == 0) { res = T::merge(res, _a[r--]); }
			l /= 2, r /= 2;
		}
		return res;
	}
	void add(int k, Monoid c) {
		k += _p2;
		_a[k] = T::merge(_a[k], c);
		for (k /= 2; k >= 1; k /= 2) {
			_a[k] = T::merge(_a[k * 2], _a[k * 2 + 1]);
		}	
	}
    Monoid operator[](int k) const { 
        return _a[_p2 + k];
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