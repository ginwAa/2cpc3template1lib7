struct BipMatching {
    const int nx, ny;
    int tag;
    vector<int> px, py, dx, dy;
    vector<vector<int>> g;
    BipMatching(int x, int y) : nx(x), ny(y), px(x, -1), py(y, -1), dx(x), dy(y), g(nx) {}; // x = size of left, y = size of right
    void addEdge(int u, int v) { g[u].emplace_back(v); }
    bool dfs(int u) {
        vector<bool> vis(ny, 0);
        for (auto v : g[u]) {
            if (!vis[v] && dy[v] == dx[u] + 1) {
                vis[v] = true;
                if (py[v] >= 0 && dy[v] == tag) continue;
                if (py[v] < 0 || dfs(py[v])) {
                    px[u] = v;
                    py[v] = u;
                    return true;
                }
            }
        } return false;
    }
    bool bfs() {
        tag = INT_MAX;
        dx.assign(nx, -1);
        dy.assign(ny, -1);
        queue<int> q;
        for (int i = 0; i < nx; ++i) if (px[i] < 0) {
            q.push(i);
            dx[i] = 0;
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (dx[u] > tag) break;
            for (auto v : g[u]) if (dy[v] < 0) {
                dy[v] = dx[u] + 1;
                if (py[v] >= 0) {
                    dx[py[v]] = dy[v] + 1;
                    q.push(py[v]);
                } else {
                    tag = dy[v];
                }
            }
        }
        return tag < INT_MAX;
    }
    int solve(){
        int ret = 0;
        while (bfs()) {
            for (int i = 0; i < nx; ++i) {
                if (px[i] < 0 && dfs(i))
                    ++ret;
            }
        }
        return ret;
    }
};
