struct bcc {
    int n, dt, ex;
    vector<int> low, dfn, stk;
    vector<vector<int>> g;
    explicit bcc(int n): n(n), low(n), dfn(n, -1), g(n) {
        stk.reserve(n);
        dt = 0;
        ex = n;
    }
    void addEdge(int u, int v) {
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    function<void(int)> dfs = [&](int u) {
        dfn[u] = low[u] = dt++;
        stk.emplace_back(u);
        for (auto v : g[u]) {
            if (dfn[v] < 0) {
                dfs(v);
                low[u] = min(low[u], low[v]);
                if (low[v] == dfn[u]) {
                    g.emplace_back(vector<int>(0));
                    int x;
                    do {
                        x = stk.back();
                        stk.pop_back();
                        g[ex].emplace_back(x);
                        g[x].emplace_back(ex);
                    } while (x != v);
                    g[ex].emplace_back(u);
                    g[u].emplace_back(ex);
                    ++ex;
                }
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }
    };
    auto get() {
        for (int i = 0; i < n; ++i) {
            if (dfn[i] < 0) {
                dfs(i);
            }
        }
        return ex;
    }
};
