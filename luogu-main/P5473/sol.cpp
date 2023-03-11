/*
 * Author: chenkaifeng @BDFZ
 */
 
#include <bits/stdc++.h>
#include "explore.h"

// void modify(int x);
// int query(int x);
// void report(int x, int y);
// int check(int x);

using namespace std;

typedef long long ll;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pf push_front
#define rep(i, s, t) for (int i = s; i <= t; ++i)
#define per(i, s, t) for (int i = t; i >= s; --i)

#define OK debug("OK!\n")
#ifndef ONLINE_JUDGE
namespace debuger{void debug(const char *s) {cerr << s;}template<typename T1,typename... T2>void debug(const char*s, const T1 x, T2...ls) { int p=0; while(*(s + p)!='\0') {if(*(s+p)=='{'&&*(s+p+1)=='}'){cerr << x;debug(s + p + 2, ls...);return;}cerr << *(s + p++);}}}using debuger::debug;
#else
#define debug(...) void(0)
#endif

std::mt19937_64 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

const int N = 3e5 + 5;

int n, m;
int a[N];
bool vis[N], inq[N];
int last[N];

void getxor(int k) {
    rep(j, 0, k) {
        rep(i, 1, n) {
            if(i >> j & 1) {
                modify(i-1);
            }
        }

        rep(i, 1, n) {
            int o = query(i-1);
            a[i] ^= ((i >> j & 1) ^ o ^ last[i]) << j;
            last[i] = o;
        }

        // rep(i, 1, n) {
        //     if(i >> j & 1) {
        //         modify(i-1);
        //     }
        // }
    }
}

void solvep() {
    int t = 0;
    int nn = n;
    while(nn) ++t, nn >>= 1;
    getxor(t);
    rep(i, 1, n) {
        if(!vis[a[i]]) {
            report(i-1, a[i]-1);
            vis[i] = vis[a[i]] = 1;
        }
    }
}

void solvet() {
    int t = 0;
    int nn = n;
    while(nn) ++t, nn >>= 1;
    --t;
    getxor(t);

    queue<int> q;
    set<pair<int, int>> vis;
    rep(i, 1, n) q.push(i), inq[i] = 1;
    while(!q.empty()) {
        int u = q.front(); q.pop();

        if(a[u] == 0) continue;
        inq[u] = 0;
        if(vis.count(mp(u, a[u]))) continue;

        auto check = [&](int u, int v) {
            if(u == v) return 0;
            if(v > n || v < 1) return 0;
            modify(u-1);
            int ok = 0;
            if(query(v-1) ^ last[v]) ok = 1;
            modify(u-1);
            return ok;
        };

        if(check(u, a[u])) {
            int x = u, y = a[u];
            a[x] ^= y;
            a[y] ^= x;
            vis.insert(mp(x, y));
            vis.insert(mp(y, x));
            q.push(x);
            q.push(y);

            report(x-1, y-1);
        }
    }
}

void solvef() {
    int t = 0;
    int nn = n;
    while(nn) ++t, nn >>= 1;
    --t;
    getxor(t);
    per(i, 2, n) {
        report(i-1, a[i]-1);
        int f = a[i];
        a[f] ^= i;
    }
}


bool ok[N];
vector<int> p;

void shuffle() {
    p.clear();
    rep(i, 1, n) if(!ok[i]) p.pb(i);
    for(int i = 0; i < p.size(); ++i) {
        int x = mtrnd() % p.size();
        int y = mtrnd() % p.size();
        swap(p[x], p[y]);
    }
}

int cnt = n, tt = 0;
vector<int> found[N];
bool fl[N];

inline void solve(int l1, int r1, vector<int>& nd) {

    if(nd.empty()) return;
    if(l1 == r1) {
        for(int u : nd) {
            ++tt;
            report(u-1, p[l1]-1);
            if(check(u-1)) ok[u] = 1, --cnt;
            if(check(p[l1]-1)) ok[p[l1]] = 1, --cnt;
            found[u].pb(p[l1]);
            found[p[l1]].pb(u);
        }
        return;
    }
    int mid = l1 + r1 >> 1;
    rep(i, l1, mid) {
        if(ok[p[i]]) continue;
        modify(p[i]-1);
        for(int v : found[p[i]]) fl[v] ^= 1;
    }
    vector<int> ndl, ndr;
    for(int u : nd) {
        if(query(u-1) ^ fl[u]) ndl.pb(u);
        else ndr.pb(u);
    }
    rep(i, l1, mid) {
        if(ok[p[i]]) continue;
        modify(p[i]-1);
        for(int v : found[p[i]]) fl[v] ^= 1;
    }
    nd.clear();
    solve(l1, mid, ndl);
    solve(mid+1, r1, ndr);
}

void solvea() {
    debug("solvea\n");
    cnt = n;
    while(tt < m) {
        // debug("cnt = {}\n", cnt);
        shuffle();
        vector<int> v;
        int nn = p.size();
        int pos = m == (int)3e5 ? nn / 3 : nn / 2;
        pos = max(pos, 1);
        for(int i = 0; i < pos; ++i) {
            modify(p[i]-1);
            for(int v : found[p[i]]) fl[v] ^= 1;
        }
        for(int i = pos; i < nn; ++i) {
            int o = p[i];
            if(!ok[o] && (query(o-1) ^ fl[o])) {
                v.pb(o);
            }
        }
        rep(i, 1, n) {
            if(!ok[i]) fl[i] = query(i-1);
        }
        solve(0, pos-1, v);
    }
}

void solveb() {
    for(int i = 0; i < n-1; ++i) {
        modify(i); 
        for(int j = i + 1; j < n; ++j) {
            int res = query(j);
            if(res ^ fl[j]) report(i, j);
            fl[j] = res;
        }
    }
}

void explore(int n, int m) {
    ::n = n, ::m = m;
    if(n <= 500) solveb();
    else if(n % 10 == 8) solvep();
    else if(n % 10 == 7) solvef();
    else if(n % 10 == 5 || n % 10 == 6) solvet();
    else solvea();
}