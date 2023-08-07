template<class T>
struct Mat {
	std::vector<std::vector<T>> val;
	int n, m;
	Mat(int n, int m, int x=0) : n(n), m(m) {
		assert(x == 0 || (n == m && x == 1));
		val.resize(n, std::vector<T>(m));
		if (x == 1) {
			for (int i = 0; i < n; i++) {
				val[i][i] = 1;
			}
		}
	}
	Mat &operator*=(const T &rhs) {
		for (auto &row : val) {
			for (auto &x : row) {
				x *= rhs;
			}
		}
		return *this;
	}	
	friend Mat operator*(const Mat &lhs, const T &rhs) {
		Mat res = lhs;
		res *= rhs;
		return res;	
	}
	friend Mat operator*(const T &lhs, const Mat &rhs) {
		Mat res = rhs;
		res *= lhs;
		return res;
	}
	Mat &operator+=(const Mat &rhs) {
		assert(n == rhs.n && m == rhs.m);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				val[i][j] += rhs.val[i][j];
			}
		}
		return *this;
	}
	friend Mat operator+(const Mat &lhs, const Mat &rhs) {
		assert(lhs.n == rhs.n && lhs.m == rhs.m);
		Mat res = lhs;
		res += rhs;
		return res;
	}
	friend Mat operator*(const Mat &lhs, const Mat &rhs) {
		assert(lhs.m == rhs.n);
		Mat res(lhs.n, rhs.m);
		for (int k = 0; k < lhs.m; k++) {
			for (int i = 0; i < lhs.n; i++) {
				for (int j = 0; j < rhs.m; j++) {
					res.val[i][j] += lhs.val[i][k] * rhs.val[k][j];
				}
			}
		}
		return res;
	}
	Mat &operator*=(const Mat &rhs) {
		assert(m == rhs.n);
		auto res = (*this) * rhs;
		*this = std::move(res);
		return *this;
	}	
};
