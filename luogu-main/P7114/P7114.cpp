/*
 * Author: chenkaifeng @BDFZ
 */

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pf push_front
#define rep(i, s, t) for (int i = s; i <= t; i++)
#define per(i, s, t) for (int i = t; i >= s; i--)

namespace nqio{const unsigned R=4e5,W=4e5;char*a,*b,i[R],o[W],*c=o,*d=o+W,h[40],*p=h,y;bool s;struct q{void r(char&x){x=a==b&&(b=(a=i)+fread(i,1,R,stdin),a==b)?-1:*a++;}void f(){fwrite(o,1,c-o,stdout);c=o;}~q(){f();}void w(char x){*c=x;if(++c==d)f();}q&operator>>(char&x){do r(x);while(x<=32);return*this;}q&operator>>(char*x){do r(*x);while(*x<=32);while(*x>32)r(*++x);*x=0;return*this;}template<typename t>q&operator>>(t&x){for(r(y),s=0;!isdigit(y);r(y))s|=y==45;if(s)for(x=0;isdigit(y);r(y))x=x*10-(y^48);else for(x=0;isdigit(y);r(y))x=x*10+(y^48);return*this;}q&operator<<(char x){w(x);return*this;}q&operator<<(char*x){while(*x)w(*x++);return*this;}q&operator<<(const char*x){while(*x)w(*x++);return*this;}template<typename t>q&operator<<(t x){if(!x)w(48);else if(x<0)for(w(45);x;x/=10)*p++=48|-(x%10);else for(;x;x/=10)*p++=48|x%10;while(p!=h)w(*--p);return*this;}}qio;}using nqio::qio;

#define OK debug("OK!\n");
#ifndef ONLINE_JUDGE
namespace debuger{void debug(const char *s) {cerr << s;}template<typename T1,typename... T2>void debug(const char*s, const T1 x, T2...ls) { int p=0; while(*(s + p)!='\0') {if(*(s+p)=='{'&&*(s+p+1)=='}'){cerr << x;debug(s + p + 2, ls...);return;}cerr << *(s + p++);}}}using debuger::debug;
#else
#define debug(...) void(0)
#endif

const int mod = 1234567891;
// const ll mod = 998244353;
template <typename T> inline void chkadd(T& x, T y) { x = x + y >= mod ? x + y - mod : x + y; }
template <typename T> inline void chkadd(T& x, T y, T z) { x = y + z >= mod ? y + z - mod : y + z; }
template <typename T> inline void chkmns(T& x, T y) { x = x - y < 0 ? x - y + mod : x - y; }
template <typename T> inline void chkmns(T& x, T y, T z) { x = y - z < 0 ? y - z + mod : y - z;}
template <typename T> inline void chkmax(T& x, T y) { x = x < y ? y : x; }
template <typename T> inline void chkmax(T& x, T y, T z) { x = y > z ? y : z; }
template <typename T> inline void chkmin(T& x, T y) { x = x < y ? x : y;}
template <typename T> inline void chkmin(T& x, T y, T z) { x = y < z ? y : z;}
ll qpow(ll x, ll p) { ll base = x, res = 1;	while (p) { if (p & 1) res = (res * base) % mod; base = (base * base) % mod; p >>= 1;} return res;}

/* template ends here */

const int N = 1.1e6 + 5;
const int L = 27;
const int base = 131;

int n;
char S[N];
int suf[N], cnt[L], pret[L];
int pw[N], hs[N];

int gethash(int s, int t) {
	int ret = (1ll * hs[t] - 1ll * hs[s-1] * pw[t-s+1]) % mod;
	if(ret < 0) ret += mod;
	return ret;
}

void solve() {
	memset(cnt, 0, sizeof cnt);
	qio >> S + 1;
	n = strlen(S + 1);
	suf[n+1] = 0;
	per(i, 1, n) {
		cnt[S[i]-'a'] ^= 1;
		suf[i] = suf[i+1] + (cnt[S[i]-'a'] ? 1 : -1);
	}
	pw[0] = 1;
	rep(i, 1, n) pw[i] = 1ll * pw[i-1] * base % mod;
	rep(i, 1, n) hs[i] = (1ll * hs[i-1] * base + S[i] - 'a') % mod;
	memset(cnt, 0, sizeof cnt);
	memset(pret, 0, sizeof pret);
	int t = 0;
	ll ans = 0;
	rep(len, 1, n) {
		int chash = gethash(1, len);
		cnt[S[len]-'a'] ^= 1;
		t += (cnt[S[len]-'a'] ? 1 : -1);
		for(int j = len; j < n; j += len) {
			if(gethash(j-len+1, j) == chash) {
				ans += pret[suf[j+1]];
			} else {
				break;
			}
		}
		rep(i, t, 26) pret[i]++;
	}
	cout << ans << "\n";
}

int main() {
	
	int t;
	qio >> t;
	while(t--) solve();
	
	return 0;
}