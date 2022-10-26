vector<int> sa_doubling(const vector<int>& s) {
    int n = int(s.size());
    vector<int> sa(n), rnk = s, tmp(n);
    iota(sa.begin(), sa.end(), 0);
    for (int k = 1; k < n; k <<= 1) {
        auto cmp = [&](int x, int y) {
            if (rnk[x] != rnk[y]) return rnk[x] < rnk[y];
            int rx = x + k < n ? rnk[x + k] : -1;
            int ry = y + k < n ? rnk[y + k] : -1;
            return rx < ry;
        };
        sort(sa.begin(), sa.end(), cmp);
        tmp[sa[0]] = 0;
        for (int i = 1; i < n; i++) {
            tmp[sa[i]] = tmp[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
        }
        swap(tmp, rnk);
    }
    return sa;
}
vector<int> sa_is(const vector<int>& s, int up = 255) {
    int n = int(s.size());
    if (n == 0) return {};
    if (n == 1) return {0};
    if (n == 2) {
        return {s[0] >= s[1], s[0] < s[1]};
    }
    vector<int> sa(n), ls(n), suml(up + 1), sums(up + 1);
    for (int i = n - 2; i >= 0; i--) {
        ls[i] = (s[i] == s[i + 1]) ? ls[i + 1] : (s[i] < s[i + 1]);
    }
    for (int i = 0; i < n; i++) {
        if (!ls[i]) {
            sums[s[i]]++;
        } else {
            suml[s[i] + 1]++;
        }
    }
    for (int i = 0; i <= up; i++) {
        sums[i] += suml[i];
        if (i < up) suml[i + 1] += sums[i];
    }
    auto induce = [&](const vector<int>& lms) {
        fill(sa.begin(), sa.end(), -1);
        vector<int> buf(up + 1);
        copy(sums.begin(), sums.end(), buf.begin());
        for (auto d : lms) {
            if (d != n) sa[buf[s[d]]++] = d;
        }
        copy(suml.begin(), suml.end(), buf.begin());
        sa[buf[s[n - 1]]++] = n - 1;
        for (int i = 0; i < n; i++) {
            int v = sa[i] - 1;
            if (v >= 0 && !ls[v]) {
                sa[buf[s[v]]++] = v;
            }
        }
        copy(suml.begin(), suml.end(), buf.begin());
        for (int i = n - 1; i >= 0; i--) {
            int v = sa[i] - 1;
            if (v >= 0 && ls[v]) {
                sa[--buf[s[v] + 1]] = v;
            }
        }
    };
    vector<int> lmsmp(n + 1, -1), lms;
    int m = 0;
    for (int i = 1; i < n; i++) {
        if (!ls[i - 1] && ls[i]) {
            lmsmp[i] = m++;
        }
    }
    for (int i = 1; i < n; i++) {
        if (!ls[i - 1] && ls[i]) {
            lms.push_back(i);
        }
    }
    induce(lms);
    if (m) {
        vector<int> sortdLms;
        for (int v : sa) {
            if (lmsmp[v] != -1) sortdLms.push_back(v);
        }
        vector<int> recs(m);
        int recup = 0;
        recs[lmsmp[sortdLms[0]]] = 0;
        for (int i = 1; i < m; i++) {
            int l = sortdLms[i - 1], r = sortdLms[i];
            int end_l = (lmsmp[l] + 1 < m) ? lms[lmsmp[l] + 1] : n;
            int end_r = (lmsmp[r] + 1 < m) ? lms[lmsmp[r] + 1] : n;
            bool same = 1;
            if (end_l - l != end_r - r) {
                same = 0;
            } else {
                while (l < end_l && s[l] == s[r]) ++l, ++r;
                if (l == n || s[l] != s[r]) same = 0;
            }
            recs[lmsmp[sortdLms[i]]] = recup += !same;
        }
        auto recsa = sa_is(recs, recup);
        for (int i = 0; i < m; i++) {
            sortdLms[i] = lms[recsa[i]];
        }
        induce(sortdLms);
    }
    return sa;
}
vector<int> lcp(const vector<int>& s, const vector<int>& sa) {
    int n = int(s.size());
    assert(n >= 1);
    vector<int> rnk(n);
    for (int i = 0; i < n; i++) {
        rnk[sa[i]] = i;
    }
    vector<int> lcp(n - 1);
    int h = 0;
    for (int i = 0; i < n; i++) {
        if (h > 0) h--;
        if (rnk[i] == 0) continue;
        int j = sa[rnk[i] - 1];
        for (; j + h < n && i + h < n; h++) {
            if (s[j + h] != s[i + h]) break;
        }
        lcp[rnk[i] - 1] = h;
    }
    return lcp;
}
