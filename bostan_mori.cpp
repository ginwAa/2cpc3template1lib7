#incldue "modulus.cpp"
struct linear {
    vector<int> _d, _md;
    void mul(vector<mint> &a, vector<mint> &b) {
        int k = b.size();
        vector<mint> _c(k << 1);
        for (int i = 0; i < k; ++i) if (a[i]) {
            for (int j = 0; j < k; ++j) _c[i + j] += a[i] * b[j];
        }
        for (int i = k + k - 1; i >= k; --i) if (_c[i]) {
            for (auto j : _d) _c[i - k + j] -= _c[i] * _md[j];
        }
        copy(_c.begin(), _c.begin() + k, a.begin());
    }
    mint solve(long long n, vector<mint> &a, const vector<mint>& b) {
        mint ans = 0;
        int z = 0, k = a.size();
        assert(k == b.size());
        vector<mint> res(k);
        res[0] = 1;
        _md.assign(k + 1, 1);
        for (int i = 0; i < k; ++i) {
            _md[k - i - 1] = -a[i].val();
        }
        _d.clear();
        for (int i = 0; i < k; ++i) if (_md[i]) {
            _d.emplace_back(i);
        }
        for (int i = __lg(1ull * n << 1); i >= 0; --i) {
            mul(res, res);
            if (n >> i & 1) {
                for (int j = k - 1; j >= 0; --j) res[j + 1] = res[j];
                res[0] = 0;
                for (auto j : _d) res[j] -= res[k] * _md[j];
            }
        }
        for (int i = 0; i < k; ++i) ans += res[i] * b[i];
        return ans;
    }
    vector<mint> BM(vector<mint> s) {
        vector<mint> C(1, 1), B(1, 1);
        int l = 0, m = 1, b = 1;
        for (int n = 0; n < s.size(); ++n) {
            mint d = 0;
            for (int i = 0; i <= l; ++i) d += C[i] * s[n - i];
            if (!d) {
                ++m;
                continue;
            }
            mint c = MOD - d / b;
            auto t = C;
            while (C.size() < B.size() + m) C.emplace_back(0);
            for (int i = 0; i < B.size(); ++i) C[i + m] += c * B[i];
            if (2 * l <= n) {
                l = n + 1 - l;
                B = t;
                b = d.val();
                m = 1;
            } else {
                ++m;
            }
        }
        return C;
    }
    mint get(vector<mint> a, long long n) {
        vector<mint> c = BM(a);
        c.erase(c.begin());
        for (auto &i : c) i = -i;
        return solve(n, c, vector<mint>(a.begin(), a.begin() + c.size()));
    }
};
