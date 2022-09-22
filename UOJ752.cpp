// Problem: C. Border 的第五种求法
// Contest: UOJ - UOJ NOI Round #6 Day2
// URL: https://uoj.ac/contest/78/problem/752
// Memory Limit: 1200 MB
// Time Limit: 6000 ms
// Create Time: 2022-08-07 10:59:24
// Input/Output: stdin/stdout
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pf push_front
#define rep(i, s, t) for (int i = s; i <= t; ++i)
#define per(i, s, t) for (int i = t; i >= s; --i)

const int N = 5e5 +5;

int n, m = 300;
int sa[N], rk[N<<1], oldrk[N], cnt[N], tmp[N], h[N], st[22][N], lg2[N];
char s[N];

inline bool compare(int i, int j, int w) {
    return oldrk[i] == oldrk[j] && oldrk[i + w] == oldrk[j + w];
}

void SA() {
    rep(i, 1, n) rk[i] = s[i];
    int p = 300;
    rep(j, 0, 20) {
        memcpy(oldrk, rk, sizeof oldrk);
        rep(i, 0, p) cnt[i] = 0;
        rep(i, 1, n) ++cnt[rk[i + (1 << j)]];
        rep(i, 1, p) cnt[i] += cnt[i-1];
        per(i, 1, n) tmp[cnt[rk[i + (1 << j)]]--] = i;
        rep(i, 0, p) cnt[i] = 0;
        rep(i, 1, n) ++cnt[rk[i]];
        rep(i, 1, p) cnt[i] += cnt[i-1];
        per(i, 1, n) sa[cnt[rk[tmp[i]]]--] = tmp[i];
        p = 1;
        rk[sa[1]] = 1;
        rep(i, 2, n) {
            p += !compare(sa[i], sa[i-1], 1 << j);
            rk[sa[i]] = p;
        }
        if(p == n) break;
    }
}

void buildheight() {
    int p = 0;
    rep(i, 1, n) {
        if (p) --p;
        while (i + p <= n && sa[rk[i] - 1] + p <= n && s[i + p] == s[sa[rk[i] - 1] + p]) p++;
        h[rk[i]] = p;
    }
}

void buildst() {
    rep(i, 1, n) st[0][i] = h[i];
    rep(j, 1, 21) {
        rep(i, 1, n) {
            if (i + (1 << j) - 1 > n)  break;
            st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << j - 1)]);
        }
    }
    lg2[0] = -1;
    rep(i, 1, n) lg2[i] = lg2[i >> 1] + 1;
}

inline int querystmin(int l, int r) {
    return min(st[lg2[r - l + 1]][l], st[lg2[r - l + 1]][r - (1 << lg2[r - l + 1]) + 1]);
}

inline int lcp(int x, int y) {
    if (x == y) return n + 1;
    x = rk[x];
    y = rk[y];
    if (x > y) swap(x, y);
    return querystmin(x + 1, y);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	return 0;
}
