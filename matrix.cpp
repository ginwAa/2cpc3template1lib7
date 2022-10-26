struct matrix {
    int n, m;
    int ma[2][2];
    matrix(int n, int m) :n(n), m(m) { reset();}
    matrix() :matrix(2, 2) {}
    void reset() {
        memset(ma, 0, sizeof ma);
    }
    matrix operator*=(const matrix& B) {
        assert(m == B.n);
        matrix C(n, B.m);
        for (int i = 0; i < n; ++i) for (int k = 0; k < B.n; ++k) {
            long long r = ma[i][k];
            for (int j = 0; j < B.m; ++j) {
                C.ma[i][j] += r * B.ma[k][j] % MOD;
                if (C.ma[i][j] >= MOD) C.ma[i][j] -= MOD;
            }
        }
        return *this = C;
    }
    matrix operator+=(const matrix& B) {
        assert(n == B.n && m == B.m);
        for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) {
            ma[i][j] += B.ma[i][j];
            if (ma[i][j] >= MOD) ma[i][j] -= MOD;
        }
        return *this;
    }
    matrix operator*(const matrix& B) {
        auto t = *this;
        return t *= B;
    }
    matrix operator+(const matrix& B) {
        auto t = *this;
        return t += B;
    }
};
matrix unit(int n, int v) {
    matrix ret(n, n);
    for (int i = 0; i < n; ++i) ret.ma[i][i] = v;
    return ret;
}
matrix power(const matrix& A, long long b) {
    assert(A.n == A.m);
    matrix base = A, ret = unit(A.n, 1);
    while (b) {
        if (b & 1) {
            ret *= base;
        }
        base *= base;
        b >>= 1;
    }
    return ret;
}
