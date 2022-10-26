#include "scc.cpp"
struct twosat {
    int n;
    vector<bool> choose;
    scc sc;
    explicit twosat(int n) : n(n), choose(n), sc(n * 2) {}
    void addClause(int u, int fu, int v, int fv) {//u-v conflict
        sc.addEdge(2 * u + !fu, 2 * v + fv);
        sc.addEdge(2 * v + !fv, 2 * u + fu);
    }
    bool satisfiable() {
        auto id = sc.get().second;
        for (int i = 0; i < n; i++) {
            if (id[i << 1] == id[i << 1 | 1]) return false;
            choose[i] = (id[i << 1] < id[i << 1 | 1]);
        }
        return true;
    }
};
