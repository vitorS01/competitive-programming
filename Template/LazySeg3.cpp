struct Node {
int v;
};
 
struct Seg3 {
    Node seg3[4*MAXN];
    int lazy[4*MAXN];
    void flush(int i, int l, int r) {
        seg3[i].v += (r-l+1)*lazy[i];
        if (l != r) {
            lazy[2*i] += lazy[i];
            lazy[2*i+1] += lazy[i];
        } 
        lazy[i] = 0;
    }
    Node join(Node a, Node b) {
        Node r;
        r.v = a.v + b.v;
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
    void update(int i, int l, int r, int tl, int tr, int x) {
        flush(i,l,r);
        if (tr < l || tl > r) return;
        if (l>=tl && r <= tr) {
            lazy[i] += x;
            flush(i,l,r);
            return;
        }
        int mid =(l+r)>>1;
        update(2*i,l,mid,tl,tr,x);
        update(2*i+1,mid+1,r,tl,tr,x);
        seg3[i] = join(seg3[2*i],seg3[2*i+1]);
    }
    int query(int i, int l, int r, int tl, int tr) {
        flush(i,l,r);
        if (tr < l || tl > r) return 0;
        if (l >= tl && r <= tr) return seg3[i].v;
        int mid =(l+r)>>1;
        return query(2*i,l,mid,tl,tr) + query(2*i+1,mid+1,r,tl,tr);
    }
};
