#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)
#define fi first
#define se second
#define pb push_back
#define mp make_pair

const int N = 1e5 + 5;
const int base = 131;
const int P1 = 1234567891;
const int P2 = 998244353;

int n, q;
ll pre[N];
char s[N<<1];
int sa[N], rk[N], h[N];
int hash1[N], hash2[N];
int pw1[N], pw2[N];
int mi1[21][N], mi2[21][N];

inline bool iseq(int i1, int j1, int i2, int j2) {
    int h11 = (hash1[j1] - 1ll * hash1[i1-1] * pw1[j1-i1+1]) % P1; if(h11 < 0) h11 += P1;
    int h12 = (hash2[j1] - 1ll * hash2[i1-1] * pw2[j1-i1+1]) % P2; if(h12 < 0) h12 += P2;
    int h21 = (hash1[j2] - 1ll * hash1[i2-1] * pw1[j2-i2+1]) % P1; if(h21 < 0) h21 += P1;
    int h22 = (hash2[j2] - 1ll * hash2[i2-1] * pw2[j2-i2+1]) % P2; if(h22 < 0) h22 += P2;
    return h11 == h21 && h12 == h22;
}

int main() {
    freopen("substring.in", "r", stdin);
    freopen("substring.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> (s + 1);
    n = strlen(s + 1);
    pw1[0] = pw2[0] = 1;
    rep(i, 1, n) {
	pw1[i] = 1ll * pw1[i-1] * base % P1;
	pw2[i] = 1ll * pw2[i-1] * base % P2;
	hash1[i] = (1ll * hash1[i-1] * base + s[i]) % P1;
	hash2[i] = (1ll * hash2[i-1] * base + s[i]) % P2;
    }
    rep(i, 1, n) sa[i] = i;

    sort(sa + 1, sa + n + 1,
	 [&](int i, int j) {
	     //cerr << "compare = " << i << " " << j << "\n";
	     int l = 1, r = n - max(i, j) + 1;
	     int p = -1;
	     while(l <= r) {
		 int mid = l + r >> 1;
		 if(iseq(i, i + mid - 1, j, j + mid - 1)) {
		     l = mid + 1;
		 } else {
		     p = mid;
		     r = mid - 1;
		 }
	     }
	     //cerr << "get differ at " << p << "\n";
	     if(p == -1) return i > j;
	     return s[i + p - 1] < s[j + p - 1];
	 });

    rep(i, 1, n) rk[sa[i]] = i;

    int p = 0;
    rep(i, 1, n) {
	if(p) --p;
	while(i + p <= n && sa[rk[i]-1] + p <= n && s[i + p] == s[sa[rk[i]-1] + p]) ++p;
	h[rk[i]] = p;
	//cerr << i << " " << sa[rk[i]-1] << " " << p << "\n";
    }

    rep(i, 1, n) {
	pre[i] = pre[i-1] + (n - sa[i] + 1) - h[i];
    }

    rep(i, 1, n) mi1[0][i] = h[i], mi2[0][i] = sa[i];
    rep(j, 1, 20) rep(i, 1, n) {
	if(i + (1 << j) - 1 > n) break;
	mi1[j][i] = min(mi1[j-1][i], mi1[j-1][i+(1<<j-1)]);
	mi2[j][i] = min(mi2[j-1][i], mi2[j-1][i+(1<<j-1)]);
    }

    //rep(i, 1, n) cerr << sa[i] << " " << h[i] << " " << pre[i] << " " << &s[sa[i]] << "\n";
    
    cin >> q;

    while(q--) {
	ll k;
	cin >> k;
	int pos = lower_bound(pre + 1, pre + n + 1, k) - pre;
	if(pos > n) {
	    cout << 0 << " " << 0 << "\n";
	    continue;
	}
	int x = k - pre[pos-1] + h[pos];
	int pp = pos + 1;
	int res = sa[pos];
	per(j, 0, 20) {
	    if(pp + (1 << j) - 1 <= n) {
		if(mi1[j][pp] >= x) {
		    res = min(res, mi2[j][pp]);
		    pp += 1 << j;
		}
	    }
	}
	cout << res << " " << res + x - 1 << "\n";
    }
    cout.flush();
    
    return 0;
}
