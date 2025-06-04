//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <class T>
using Tree =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

//#define int long long
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fi first
#define se second
#define rep(i, a, b) for (int i = a; i <= b; ++i)
#define per(i, b, a) for (int i = b; i >= a; --i)
#define pb push_back
#define eb emplace_back
#define all(v) (v).begin(), (v).end()
#define lsb(x) (x)&(-x)
 
void setIO(string name = "") {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    if (!name.empty()) {
        freopen((name + ".in").c_str(), "r", stdin);
        freopen((name + ".out").c_str(), "w", stdout);
    }
}
ll fexp(ll a, ll b, ll m) {
    if (b == 0) return 1LL;
    ll p = a;
    ll ans = 1;
 
    while (b > 0) {
        if (b % 2 != 0) ans = (ans*p)%m;
        p = (p*p)%m;
        b >>= 1;
    }
    return ans;
}
 
const int MAXN = 2e5 + 10;
//const int INF = 1e18+5;
const int MOD = 1e9+7;
vector<int> g[MAXN], id[25010], cmp[25010];
int ti[MAXN], to[MAXN], R[MAXN], dp[510][25000], mp[25010],q,n,r, t= 0;
// there can't be too many heavy groups!

void dfs(int u, int p = -1) {
    ti[u] = t++;
    cmp[R[u]].pb(ti[u]);
    for (const int &v : g[u]) {
        if (v==p) continue;
        dfs(v,u);
    }
    to[u] = t++;
}
void dfs2(int u, int m, int cur = 0, int p = -1) {
    dp[mp[m]][R[u]] += cur; 
    for (const int &v : g[u]) {
        if (v==p) continue;
        dfs2(v,m, cur + (R[u]==m),u);
    }
}

int HH(int a, int b) {
    return dp[mp[a]][b];
}
int LH(int a, int b) {
    int ans = 0;
    for (auto &i: id[a]) {
        ans += (lower_bound(all(cmp[b]), to[i]) - lower_bound(all(cmp[b]), ti[i]));
    }

    return ans;
}


void solve() {
    cin >> n >> r >> q;
    cin >> R[1];
    id[R[1]].pb(1);
    rep(i,2,n) {
        int pr,rg;cin >> pr >> rg;
        R[i] = rg;
        id[rg].pb(i);
        g[i].pb(pr);
        g[pr].pb(i);
    }
    dfs(1);
    int cc = 1;
    int HEAVY_THRESHOLD = 500;
    rep(i,1,r) {
        if (id[i].size() >HEAVY_THRESHOLD) {
            mp[i] = cc++;
            dfs2(1,i);
        }
    }

    while (q--) {
        int a,b;cin >> a >> b;
        bool ha = id[a].size() > HEAVY_THRESHOLD, hb = id[b].size() > HEAVY_THRESHOLD;
        int ans;
        if (ha) ans = HH(a,b);
        else ans = LH(a,b);
        cout << ans << endl;
        cout << flush;
    }
}


int32_t main() {
    setIO();
    int tt = 1;
    //cin >> tt;

    while (tt-- > 0) solve();
    
}
