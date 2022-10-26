const int MOD = 998244353;
struct mint {
public:
    mint(int _v = 0) {
        v = _v;
        if (v < 0) v += MOD;
        else if (v >= MOD) v -= MOD;
    }
    mint(long long v_) {
        v = v_ % MOD;
        if (v < 0) v += MOD;
    }
    int val() const { return v; }
    mint& operator++() {
        if (++v == MOD) v = 0;
        return *this;
    }
    mint& operator--() {
        if (--v == 0) v = MOD - 1;
        return *this;
    }
    mint operator++(int) {
        mint result = *this;
        ++*this;
        return result;
    }
    mint operator--(int) {
        mint result = *this;
        --*this;
        return result;
    }
    mint& operator+=(const mint& rhs) {
        v += rhs.v;
        if (v >= MOD) v -= MOD;
        return *this;
    }
    mint& operator-=(const mint& rhs) {
        v -= rhs.v;
        if (v < 0) v += MOD;
        return *this;
    }
    mint& operator*=(const mint& rhs) {
        v = (long long)v * rhs.v % MOD;
        return *this;
    }
    mint& operator/=(const mint& rhs) { return *this = *this * rhs.inv(); }
    mint operator+() const { return *this; }
    mint operator-() const { return mint() - *this; }
    mint pow(long long n) const {
        assert(0 <= n);
        mint x = *this, r = 1;
        while (n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }
    mint inv() const { return pow(MOD - 2);}
    friend mint operator+(const mint& lhs, const mint& rhs) {
        return mint(lhs) += rhs;
    }
    friend mint operator-(const mint& lhs, const mint& rhs) {
        return mint(lhs) -= rhs;
    }
    friend mint operator*(const mint& lhs, const mint& rhs) {
        return mint(lhs) *= rhs;
    }
    friend mint operator/(const mint& lhs, const mint& rhs) {
        return mint(lhs) /= rhs;
    }
    friend bool operator==(const mint& lhs, const mint& rhs) {
        return lhs.v == rhs.v;
    }
    friend bool operator!=(const mint& lhs, const mint& rhs) {
        return lhs.v != rhs.v;
    }
    friend istream& operator>>(istream &is, mint &X) { 
        long long u; 
        is >> u; 
        X = mint(u); 
        return is; 
    }
    friend ostream& operator<<(ostream &os, const mint &X){
        return os << X.v;
    }
    bool operator<(const mint &X) const {return v < X.v;}
    bool operator==(const mint &X) const {return v == X.v;}
    bool operator!=(const mint &X) const {return v != X.v;}
    explicit operator bool() const {return v;}
private:
    int v;
};
