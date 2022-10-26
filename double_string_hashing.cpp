struct strhsh {
    const int M = 1e9 + 7, B = 281;
    vector<int> hv;
    strhsh() {}
    strhsh(const string& s) {
        hv.emplace_back(0);
        append(s);
    }
    void append(const string& s) {
        long long t = hv.back();
        for (int i = 0; i < s.size(); ++i) {
            t = t * B % M;
            t += s[i];
            hv.emplace_back(t < M ? t : t - M);
            t = hv.back();
        }
    }
    int subhsh(int l, int r) {
        assert(r < hv.size());
        int t = qpow(B, r - l, M) * hv[l] % M;
        if (t < 0) t += M;
        t = hv[r] - t;
        return t < 0 ? t + M : t;
    }
};
struct strhsh2 {
    const int M = 1e9 + 9, B = 719;
    vector<int> hv;
    strhsh2():hv(0, 0) {}
    strhsh2(const string& s):hv(0, 0) {
        append(s);
    }
    void append(const string& s) {
        long long t = hv.back();
        for (int i = 0; i < s.size(); ++i) {
            t = t * B % M;
            t += s[i];
            hv.emplace_back(t < M ? t : t - M);
            t = hv.back();
        }
    }
    int subhsh(int l, int r) {
        assert(r < hv.size());
        int t = qpow(B, r - l, M) * hv[l] % M;
        if (t < 0) t += M;
        t = hv[r] - t;
        return t < 0 ? t + M : t;
    }
};
