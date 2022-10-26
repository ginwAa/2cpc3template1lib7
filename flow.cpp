strcut Flow {
    static constexpr long long INF = 1e18;
    const int V;
    struct Edge {
        int to; 
        long long cap;
        Edge(int to, long long cap) : to(to), cap(cap) {};
    };
    vector<int> cur, h;
    vector<Edge> e; 
    vector<vector<int>> g;
    Flow(int n) : V(n), cur(V), h(V), g(V) {};
    void addEdge(int u, int v, long long c) {
        g[u].emplace_back(e.size()); e.emplace_back(v, c);
        g[v].emplace_back(e.size()); e.emplace_back(u, 0);//if undirect -> cap = c
    }
    bool bfs(int s, int t) {
        h.assign(V, -1); h[s] = 0;
        queue<int> q; q.push(s);
        while (!q.empty()) {
            int u = q.front(); 
            q.pop();
            for (int i : g[u]) {
                int v = e[i].to;
                if (e[i].cap > 0 && h[v] == -1) {
                    h[v] = h[u] + 1;
                    if (v == t) return 1;
                    q.push(v);
                }
            }
        } 
        return 0;
    }
    long long dfs(int u, int s, long long up) {
        if (u == s) return up;
        long long res = 0;
        for (int& i = cur[u]; i < g[u].size(); ++i) {
            int j = g[u][i]; 
            int v = e[j].to;
            if (e[j ^ 1].cap > 0 && h[u] > h[v]) {
                long long d = dfs(v, s, min(e[j ^ 1].cap, up - res));
                if (d <= 0) continue;
                e[j ^ 1].cap -= d;
                e[j].cap += d;
                res += d;
                if (res == up) return res;
            }
        }
        h[u] = V;
        return res;
    }
    long long maxFlow(int s, int t) {
        long long mxflow = 0;
        while (bfs(s, t)) {
            cur.assign(V, 0);
            long long d = dfs(t, s, INF);
            if (!d) break;
            mxflow += d;
        }
        return mxflow;
    }
};
