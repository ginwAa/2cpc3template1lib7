struct CostFlow {
    struct Edge {
        int to, cap, w; //w : cost
        Edge(int to, int cap, int w) : to(to), cap(cap), w(w) {}
    };
    const int V;
    vector<int> pre; //pre: index of previous edge
    vector<long long> dis, h;
    vector<Edge> e; 
    vector<vector<int>> g;//G[u]: indeces of edge from vertice u
    CostFlow(int _n) : V(_n), g(V) {};
    void addEdge(int u, int v, int cap, int w) {
        g[u].emplace_back(e.size()); e.emplace_back(v, cap, w);
        g[v].emplace_back(e.size()); e.emplace_back(u, 0, -w);
    }
    bool Dijkstra(int s, int t) {
        dis.assign(V, LLONG_MAX);
        pre.assign(V, -1);
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> que;
        que.emplace(0, s);
        dis[s] = 0;
        while (!que.empty()) {
            auto [d, u] = que.top();
            que.pop();
            if (dis[u] != d)continue;
            for (auto i : g[u]) {
                auto& [v, cap, w] = e[i];
                if (cap > 0 && dis[v] > h[u] - h[v] + d + w) {
                    dis[v] = h[u] - h[v] + d + w; 
                    pre[v] = i; 
                    que.emplace(dis[v], v);
                }
            }
        } 
        return dis[t] != LLONG_MAX;
    }
    pair<int, long long> MCMF(int s, int t) { //flow cost
        h.resize(V, 0);
        long long Cost = 0;
        int Flow = 0, aug = INT_MAX;
        while (Dijkstra(s, t)) {
            aug = INT_MAX;
            for (int i = 0; i < V; ++i) {
                h[i] += dis[i];
            }
            for (int i = t; i != s; i = e[pre[i] ^ 1].to) {
                aug = min(aug, e[pre[i]].cap);
            }
            for (int i = t; i != s; i = e[pre[i] ^ 1].to) {
                e[pre[i]].cap -= aug;
                e[pre[i] ^ 1].cap += aug;
            }
            Flow += aug;
            Cost += h[t] * aug;
        }
        return make_pair(Flow, Cost);
    }
};
