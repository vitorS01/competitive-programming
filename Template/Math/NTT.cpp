const int MOD = 998244353;
const int G = 3;
const int INV_2 = 499122177;

int fexp(int a, int b) {
    int ans = 1, cur = a;
    while (b>0) {
        if(b&1) ans = (ans*cur)%MOD;
        cur = cur*cur%MOD;
        b>>=1;
    }
    return ans;
}

void fft(vector<int> &a, bool inv = 0) {
    int n = a.size();
    if(n==1) return;
    
    vector<int> a0(n/2), a1(n/2);
    rep(i,0,n/2 - 1) {
        a0[i] = (a[2*i]);
        a1[i] = (a[2*i+1]);
    }

    fft(a0, inv);
    fft(a1, inv);

    int w = 1, wn;
    if(inv) wn = fexp(G, MOD - 1 - (MOD-1)/n);
    else wn = fexp(G, (MOD-1)/n);

    rep(i,0,n/2 - 1) {
        int u = a0[i], v = w*a1[i]%MOD;
        a[i] = (u + v) %MOD;
        a[i+n/2] = (u - v + MOD)%MOD;
        if(inv) {
            a[i] = a[i]*INV_2%MOD;
            a[i+n/2] = a[i+n/2]*INV_2%MOD;
        }
        w = w*wn%MOD;
    }
}
