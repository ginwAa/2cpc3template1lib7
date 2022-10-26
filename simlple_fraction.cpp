struct frac {
    int num;
    int den;
    frac(): num(0), den(1) {}
    frac(int num, int den): num(num), den(den) {
        assert(den != 0);
    }
    bool operator <(const frac &a) const {
        return 1LL * num * a.den < 1LL * a.num * den;
    }
    bool operator ==(const frac &a) const {
        return 1LL * num * a.den == 1LL * a.num * den;
    }
    explicit operator bool() const {return num;}
};
