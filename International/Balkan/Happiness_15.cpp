#include "happiness.h"
#include <bits/stdc++.h>
using std::min;

#define ll long long
#define rep(i, a, b) for (int i = a; i <= b; ++i)
#define per(i, b, a) for (int i = b; i >= a; --i)

const long long INF = 1e18 + 5;

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

ll s = 0, m;
std::map<ll,ll> mp;


bool init(int coinsCount, long long maxCoinSize, long long coins[]) {
	m = maxCoinSize;
	rep(i,0,coinsCount-1) {
		ll x = coins[i];
        s+=x;
        mp[x]++;
        seg.update(seg.root,1,m,x+1,m,x);
        if (mp[x]==1) seg.update(seg.root,1,m,x,x,-x);
    }
    if (s == 0) return 1;
	
	ll mn = seg.query(seg.root,1,m,1,min(m,s));
    return (mp[1]>0 && mn >= 0);
}

bool is_happy(int event, int coinsCount, long long coins[]) {
    rep(i,0,coinsCount-1) {
		ll x = coins[i];
        s += x*event;
        mp[x] += event;
        seg.update(seg.root,1,m,x+1,m,x*event);
        if (mp[x] == 0 || (mp[x]==1 && event==1)) seg.update(seg.root,1,m,x,x,-x*event);
    }
    if (s == 0) return 1;

    ll mn = seg.query(seg.root,1,m,1,min(m,s));
    return (mp[1]>0 && mn >= 0);
}
