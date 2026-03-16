//https://cp-algorithms.com/algebra/fft.html
using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd> &a, bool inv = 0) {
    int n = a.size();
    if(n==1) return;
    
    vector<cd> a0(n/2), a1(n/2);
    rep(i,0,n/2 - 1) {
        a0[i] = (a[2*i]);
        a1[i] = (a[2*i+1]);
    }

    fft(a0, inv);
    fft(a1, inv);

    double ang = 2*PI/n*(inv?-1:1);
    cd w(1), wn(cos(ang),sin(ang));
    rep(i,0,n/2 - 1) {
        a[i] = a0[i] + w*a1[i];
        a[i+n/2] = a0[i] - w*a1[i];
        if(inv) {
            a[i] /= 2;
            a[i+n/2] /=2;
        }
        w *= wn;
    }
}
