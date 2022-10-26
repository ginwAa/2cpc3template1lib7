template <typename T>
struct BCMatching {
    const T INF = numeric_limits<T>::max();
    vector<bool> visx, visy;
    vector<int> px, py, pre;//px u -> v py v -> u
    vector<T> lx, ly, slack;
    queue<int> q;
    bool check(int v) {
        visy[v] = true;
        if (~py[v]) {
            q.push(py[v]);
            visx[py[v]] = true;
            return false;
        }
        while (~v) 
            swap(v, px[py[v] = pre[v]]);
        return true;
    }
    T solve(const int nx, const int ny, const vector<vector<T>>& g) {//g[i][j] >= 0
        T ret = 0;
        lx.assign(nx, 0);
        ly.assign(ny, -INF);
        px.assign(nx, -1);
        py.assign(ny, -1);
        pre.assign(ny, 0);
        for (int i = 0; i < nx; ++i) 
            lx[i] = *max_element(g[i].begin(), g[i].end());
        auto bfs = [&](int k) {
            while (!q.empty()) q.pop();
            q.push(k);
            visx[k] = true;
            while (1) {
                while (!q.empty()) {
                    int u = q.front();
                    q.pop();
                    for (int v = 0; v < ny; ++v) if (!visy[v]) {
                        T d = lx[u] + ly[v] - g[u][v];
                        if (slack[v] >= d) {
                            pre[v] = u;
                            if (d) slack[v] = d;
                            else if (check(v)) return;
                        }
                    }
                }
                T a = INF;
                for (int i = 0; i < ny; ++i) 
                    if (!visy[i]) a = min(a, slack[i]);
                for (int i = 0; i < nx; ++i) 
                    if (visx[i]) lx[i] -= a;
                for (int i = 0; i < ny; ++i) 
                    if (visy[i]) ly[i] += a;
                    else slack[i] -= a;
                for (int i = 0; i < ny; ++i) 
                    if (!visy[i] && !slack[i] && check(i))
                        return;
            }
        };
        for (int i = 0; i < nx; ++i) {
            visx.assign(nx, 0);
            visy.assign(ny, 0);
            slack.assign(ny, INF);
            bfs(i);
        }
        for (int i = 0; i < nx; ++i) {
            if (px[i] >= 0) ret += g[i][px[i]];
        }
        return ret;
    }
};
