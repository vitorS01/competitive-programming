#include "happiness.h"
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define rep(i, a, b) for (int i = a; i <= b; ++i)
#define per(i, b, a) for (int i = b; i >= a; --i)

const long long INF = 1e18 + 5;

struct Node {
    array<ll,2> v = {0,1};
    Node *l = nullptr;
    Node *r = nullptr;
};
 
struct Seg3 {
    Node *root = new Node;

    void apply(Node *cur, ll x, bool ch = 0) {
        (cur->v)[0] += x*(ch>=0?1:-1);
        (cur->v)[1] -= x*ch;
        //cout << x << ' ' <<(cur->v)[1] << '\n';
    }

    array<ll,2> join(array<ll,2> a, array<ll,2> b) {
        return {a[0] + b[0], min(a[1], b[1] + a[0])};
    }

    void update(Node *cur, ll l, ll r, ll ti, ll x, bool flag = 0) {
        if (l==r && r == ti) {
            apply(cur, x, flag);
            return;
        }
        ll mid =(l+r)>>1;
        if (mid >= ti) {
        	if (!cur->l) cur->l = new Node;
        	update((cur->l),l,mid,ti,x,flag);
        	(cur->v) = join((cur->l)->v,(((cur->r)!= nullptr)?((cur->r)->v):(array<ll,2>){0,-1}));
        } else {
    		if (!cur->r) cur->r = new Node;
        	update((cur->r),mid+1,r,ti,x,flag);
        	(cur->v) = join(((cur->l) != nullptr)?((cur->l)->v):(array<ll,2>{0,-1}),((cur->r)->v));
        }

    }
    array<ll,2> query(Node *cur, ll l, ll r, ll tl, ll tr) {
    	if(!cur) return {0,1};
        if (tr < l || tl > r) return {0,1};
        if (l >= tl && r <= tr) return (cur-> v);
        ll mid = (l+r)>>1;
        return join(query((cur->l), l, mid, tl,tr), query((cur->r),mid+1,r, tl,tr));
    }
} seg;

ll s = 0, m;
map<ll,ll> mp;

bool init(int coinsCount, long long maxCoinSize, long long coins[]) {
	m = maxCoinSize;
	rep(i,0,coinsCount-1) {
		ll x = coins[i];
        s+=x;
        mp[x]++;
        seg.update(seg.root,1,m,x,x,(mp[x]==1));
    }
    if (s == 0) return 1;
	
	ll mn = seg.query(seg.root,1,m,1,min(m,s))[1];
    return (mp[1]>0 && mn >= 0);
}

bool is_happy(int event, int coinsCount, long long coins[]) {
    rep(i,0,coinsCount-1) {
		ll x = coins[i];
        s += x*event;
        mp[x]+=event;
        if (mp[x]==1&&event==1)seg.update(seg.root,1,m,x,x*event,1);
        else seg.update(seg.root,1,m,x,x*event, -(mp[x]==0));
    }
    if (s == 0) return 1;

    ll mn = seg.query(seg.root,1,m,1,min(m,s))[1];
	//cout << seg.query(seg.root,1,m,4,4)[1] << "JIJI" << '\n';

    return (mp[1]>0 && mn >= 0);
}
