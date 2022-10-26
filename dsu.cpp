struct DSU {
    int gps;
    vector<int>anc, sz;
    void reset() { 
        iota(anc.begin(), anc.end(), 0); 
        gps = anc.size();
        sz.assign(gps, 1);
    }
    DSU(int n) : gps(n), anc(n) { reset(); }
    int find(int n) {
        while (n != anc[n])n = anc[n] = anc[anc[n]];
        return n;
    }
    bool merge(int n, int m) {
        if (find(n) == find(m)) return false;
        sz[find(n)] += sz[find(m)];
        anc[find(m)] = find(n);
        --gps;
        return true;
    }
    int size(int n) { return sz[find(n)]; }
};
