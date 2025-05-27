struct Node {
int v;
};
 
struct Seg3 {
    Node seg3[4*MAXN];
    Node join(Node a, Node b) {
        Node r;
        r.v = min(a.v, b.v);
        return r;
    }
 
    void build(int i, int l, int r) {
        if (l == r) {
            Node tmp;
            tmp.v = a[l];
            seg3[i] = tmp;
            return;
        }
        int mid =(l+r)>>1;
        build(2*i,l,mid);
        build(2*i+1,mid+1,r);
        seg3[i] = join(seg3[2*i],seg3[2*i+1]);
    }
 
    Seg3(int l, int r) {
        build(1,l,r);
    }
    void update(int i, int l, int r, int ti, int x) {
        if (ti < l || ti > r) return;
        if (l==r) {
            Node tmp;
            tmp.v = x;
            seg3[i] = tmp;
            return;
        }
        int mid =(l+r)>>1;
        update(2*i,l,mid,ti,x);
        update(2*i+1,mid+1,r,ti,x);
        seg3[i] = join(seg3[2*i],seg3[2*i+1]);
    }
    int query(int i, int l, int r, int tl, int tr) {
        if (tr < l || tl > r) return INF;
        if (l >= tl && r <= tr) return seg3[i].v;
        int mid =(l+r)>>1;
        return min(query(2*i,l,mid,tl,tr),query(2*i+1,mid+1,r,tl,tr));
    }
};
