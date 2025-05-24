struct Node {
    ll v = 1;
    ll lazy = 0;
    Node *l = nullptr;
    Node *r = nullptr;
};
 
struct Seg3 {
    Node *root = new Node;

    void apply(Node*cur, ll x) {
        (cur->v) += x;
        (cur->lazy) += x;
    }

    void flush(Node *cur, int l, int r) {
        if ((cur->l) == nullptr) (cur->l) = new Node;
        if ((cur->r) == nullptr) (cur->r) = new Node;

        if (l!=r) {
            apply((cur->l), (cur->lazy));
            apply((cur->r), (cur->lazy));
        }
        (cur->lazy) = 0;
    }
    ll join(ll a, ll b) {
        return {min(a, b)};
    }

    void update(Node *cur, int l, int r, int tl, int tr, ll x) {
        if (tr < l || tl > r) return;
        if (l>=tl && r <= tr) {
            apply(cur, x);
            return;
        }
        flush(cur,l,r);
        int mid =(l+r)>>1;

        update((cur->l),l,mid,tl,tr,x);
        update((cur->r),mid+1,r,tl,tr,x);
        (cur->v) = join((cur->l)->v,(cur->r)->v);
    }
    ll query(Node *cur, int l, int r, int tl, int tr) {
        if (tr < l || tl > r) return INF;
        flush(cur,l,r);
        if (l >= tl && r <= tr) return (cur-> v);
        int mid = (l+r)>>1;
        return join(query((cur->r),mid+1,r, tl,tr), query((cur->l), l, mid, tl,tr));
    }
} seg;
