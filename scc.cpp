struct scc {
    int n, dt, gps;
    vector<int> low, dfn, ids, stk;
    vector<vector<int>> g;
    explicit scc(int n): n(n), low(n), dfn(n, -1), ids(n), g(n) {
        stk.reserve(n);
        gps = dt = 0;
    }
    void addEdge(int u, int v) {
        g[u].emplace_back(v);
        // g[v].emplace_back(u);//undirected graph
    }
    void dfs(int u) {
        low[u] = dfn[u] = dt++;
        stk.emplace_back(u);
        for (auto v : g[u]) {
            if (dfn[v] < 0) {
                dfs(v);
                low[u] = min(low[u], low[v]);
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (low[u] == dfn[u]) {
            while (1) {
                int v = stk.back();
                stk.pop_back();
                dfn[v] = n;
                ids[v] = gps;
                if (u == v) break;
            }
            ++gps;
        }
    }
    pair<int, vector<int>> get() {
        for (int i = 0; i < n; ++i) {
            if (dfn[i] < 0) {
                dfs(i);
            }
        }
        return {gps, ids};
    }
};
