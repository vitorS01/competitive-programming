struct Node {
    int dep, val;
    int l = 0, r = 0;
};

Node pool[MAXN];

int merge(int a, int b) {
    if (!a || !b) return a + b;
    if (pool[a].val > pool[b].val) swap(a, b); 
  
    pool[a].r = merge(pool[a].r, b);
    swap(pool[a].l, pool[a].r);
    return a;
}
