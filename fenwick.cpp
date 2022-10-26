template <typename T>
struct Fenwick {
    const int n;
    std::vector<T> a;
    Fenwick(int n) : n(n), a(n) {}
    void add(int x, T v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] += v;
        }
    }
    T sum(int x) {  // [0, x)
        T ans = 0;
        for (int i = x; i > 0; i -= i & -i) {
            ans += a[i - 1];
        }
        return ans;
    }
    T rangeSum(int l, int r) {
        return sum(r) - sum(l);
    }
    int upper_bound(int y) { //sum[0, j) <= y
        if (y < 0 || sum(n) < y) return -1;
        int j = 0;
        for (int k = __lg(n); k >= 0; --k) {
            if (j + (1 << k) <= n && a[j + (1 << k) - 1] <= y) {
                y -= a[j + (1 << k) - 1];
                j += 1 << k;
            }
        }
        return j;
    }
};
