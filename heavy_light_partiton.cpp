struct TrAnalyz {
	int Root, Z, _tot = -1;
	vector<int>sz, son, fa, dep, top, dfn, rnk;//rnk = id of dfn, dfn = 0123...
	TrAnalyz(const vector<vector<int>>& G, int rt) :Root(rt), Z(G.size()), sz(Z, 1), son(Z, -1),
		fa(Z, -1), dep(Z, -1), top(Z, -1), dfn(Z, -1), rnk(Z, -1) {
		function<void(int, int)>dfs1 = [&](int u, int f) {
			for (int v : G[u]) {
				if (v == f)continue;
				fa[v] = u; dep[v] = dep[u] + 1;
				dfs1(v, u);
				sz[u] += sz[v];
				if (son[u] < 0 || sz[v] > sz[son[u]]) son[u] = v;
			}
		}, dfs2 = [&](int u, int tp) {
			top[u] = tp; rnk[++_tot] = u; dfn[u] = _tot;
			if (son[u] < 0)return;
			dfs2(son[u], tp);
			for (int v : G[u]) {
				if (v == son[u] || v == fa[u])continue;
				dfs2(v, v);
			}
		}; dep[rt] = 0; dfs1(rt, -1); dfs2(rt, rt);
	}
	int LCA(int u, int v) {
		while (top[u] - top[v]) {
			if (dep[top[u]] > dep[top[v]])u = fa[top[u]];
			else v = fa[top[v]];
		}
		return dep[u] > dep[v] ? v : u;
	}
};
