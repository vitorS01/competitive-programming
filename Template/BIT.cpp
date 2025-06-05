template <class T> struct BIT {
    int n;
    vector<T> bit, arr;
    BIT(int _n) : n(_n), bit(_n + 1), arr(_n) {}
    void add(int i, T val) {
        arr[i] += val;
        for (++i; i <= n; i += lsb(i)) bit[i] += val;
    }
    void set(int i, T val) { add(i, val - arr[i]); }
    T query(int i) {
        T res = 0;
        for (++i; i > 0; i -= lsb(i)) res += bit[i];
        return res;
    }
};
