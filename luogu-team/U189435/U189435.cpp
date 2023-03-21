// Problem: U189435 子序列
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/U189435?contestId=57293
// Memory Limit: 500 MB
// Time Limit: 3000 ms

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
#define rep(i, s, t) for (int i = s; i <= t; ++i)
#define per(i, s, t) for (int i = t; i >= s; --i)

namespace nqio{const unsigned R=4e5,W=4e5;char*a,*b,i[R],o[W],*c=o,*d=o+W,h[40],*p=h,y;bool s;struct q{void r(char&x){x=a==b&&(b=(a=i)+fread(i,1,R,stdin),a==b)?-1:*a++;}void f(){fwrite(o,1,c-o,stdout);c=o;}~q(){f();}void w(char x){*c=x;if(++c==d)f();}q&operator>>(char&x){do r(x);while(x<=32);return*this;}q&operator>>(char*x){do r(*x);while(*x<=32);while(*x>32)r(*++x);*x=0;return*this;}template<typename t>q&operator>>(t&x){for(r(y),s=0;!isdigit(y);r(y))s|=y==45;if(s)for(x=0;isdigit(y);r(y))x=x*10-(y^48);else for(x=0;isdigit(y);r(y))x=x*10+(y^48);return*this;}q&operator<<(char x){w(x);return*this;}q&operator<<(char*x){while(*x)w(*x++);return*this;}q&operator<<(const char*x){while(*x)w(*x++);return*this;}template<typename t>q&operator<<(t x){if(!x)w(48);else if(x<0)for(w(45);x;x/=10)*p++=48|-(x%10);else for(;x;x/=10)*p++=48|x%10;while(p!=h)w(*--p);return*this;}}qio;}using nqio::qio;

#define OK debug("OK!\n")
#ifndef ONLINE_JUDGE
namespace debuger{void debug(const char *s) {cerr << s;}template<typename T1,typename... T2>void debug(const char*s, const T1 x, T2...ls) { int p=0; while(*(s + p)!='\0') {if(*(s+p)=='{'&&*(s+p+1)=='}'){cerr << x;debug(s + p + 2, ls...);return;}cerr << *(s + p++);}}}using debuger::debug;
#else
#define debug(...) void(0)
#endif

int qpow(int x, ll p, int mod) {
	int res = 1, base = x;
	while(p) {
		if(p & 1) res = 1ll * res * base % mod;
		base = 1ll * base * base % mod;
		p >>= 1;
	}
	return res;
}

/* template ends here */

std::mt19937 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

const int N = 1e5 + 5;
const int M = 320;

int bid[N], bl[M], br[M], siz, tot;
int cnt[M][M][M];
ll sum[M][M][M], tmp1[M];
int pre[M][N], qcnt[M], appt[N], tmp[N], tmp2[N], tmp3[M];
vector<int> pos[N], big;
int n, q, a[N];

inline int gett(int id, int l, int r) {
	auto s = lower_bound(pos[id].begin(), pos[id].end(), l);
	auto e = upper_bound(pos[id].begin(), pos[id].end(), r);
	return e - s;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cerr << int(sizeof sum) / 1024 / 1024 << "\n";
	
	cin >> n >> q;
	rep(i, 1, n) cin >> a[i], ++appt[a[i]];
	
	int B = sqrt(n);
	rep(i, 1, n) if(appt[a[i]] > B) pos[a[i]].pb(i);
	rep(i, 1, 1e5) if(appt[i] > B) big.pb(i);
	siz = sqrt(n), tot = (n + siz - 1) / siz;
	rep(i, 1, tot) bl[i] = br[i-1] + 1, br[i] = br[i-1] + siz;
	br[tot] = n;
	rep(i, 1, tot) rep(j, bl[i], br[i]) bid[j] = i;
	
	rep(i, 1, tot) {
		memset(tmp, 0, sizeof tmp);
		rep(j, i, tot) {
			memcpy(cnt[i][j], cnt[i][j-1], sizeof cnt[i][j]);
			memcpy(sum[i][j], sum[i][j-1], sizeof sum[i][j]);
			
			rep(k, bl[j], br[j]) {
				if(appt[a[k]] > B) continue;
				if(tmp[a[k]]) {
					--cnt[i][j][tmp[a[k]]];
					sum[i][j][tmp[a[k]]] -= a[k];
				}
				++tmp[a[k]];
				++cnt[i][j][tmp[a[k]]];
				sum[i][j][tmp[a[k]]] += a[k];
			}
			
			// debug("i = {}, j = {}\n", i, j);
			// cerr << "cnt = "; rep(k, 0, B) cerr << cnt[i][j][k] << " \n"[k == B];
			// cerr << "sum = "; rep(k, 0, B) cerr << sum[i][j][k] << " \n"[k == B];
		}
	}
	rep(i, 1, tot) {
		memcpy(pre[i], pre[i-1], sizeof pre[i]);
		rep(j, bl[i], br[i]) ++pre[i][a[j]];
	}
	
	debug("init ok\n");
	
	while(q--) {
		int l, r, P;
		cin >> l >> r >> P;
		int ans = 0;
		for(int x : big) {
			int cc = gett(x, l, r);
			ans = (1ll * (qpow(2, cc, P) - 1) * qpow(2, r-l+1 - cc, P) % P * x + ans) % P;
		}
		
		debug("id = {} {}\n", bid[l], bid[r]);
		
		if(bid[l] == bid[r]) {
			memset(tmp1, 0, sizeof tmp1);
			rep(i, l, r) {
				if(appt[a[i]] <= B) {
					if(tmp2[a[i]]) tmp1[tmp2[a[i]]] -= a[i];
					++tmp2[a[i]];
					tmp1[tmp2[a[i]]] += a[i];
					debug("t = {}\n", tmp2[a[i]]);
				}
			}
			rep(i, l, r) tmp2[a[i]]  = 0;
			rep(i, 1, B) {
				if(tmp1[i]) {
					debug("get i = {}, tmp = {}\n", i, tmp2[i]);
					ans = (1ll * (qpow(2, i, P) - 1) * (tmp1[i] % P) % P * qpow(2, r-l+1-i, P) + ans) % P;
				}
			}
			ans = (ans + P) % P;
		} else {
			int b1 = bid[l], b2 = bid[r];
			memcpy(tmp1, sum[b1+1][b2-1], sizeof tmp1);
			memcpy(tmp3, cnt[b1+1][b2-1], sizeof tmp3);
			
			rep(i, l, br[b1]) {
				if(appt[a[i]] > B) continue;
				int t = tmp2[a[i]] + pre[b2-1][a[i]] - pre[b1][a[i]];
				tmp1[t] -= a[i];
				--tmp3[t];
				
				++tmp2[a[i]];
				++t;
				tmp1[t] += a[i];
				++tmp3[i];
			}
			
			rep(i, bl[b2], r) {
				if(appt[a[i]] > B) continue;
				int t = tmp2[a[i]] + pre[b2-1][a[i]] - pre[b1][a[i]];
				tmp1[t] -= a[i];
				--tmp3[t];
				
				++tmp2[a[i]];
				++t;
				tmp1[t] += a[i];
				++tmp3[i];
			}
			
			rep(i, 1, B) {
				if(tmp1[i]) {
					debug("get i = {}, tmp = {}\n", i, tmp1[i]);
					ans = (1ll * (qpow(2, i, P) - 1) * (tmp1[i] % P) % P * qpow(2, r-l+1-i, P) + ans) % P;
				}
			}
			
			rep(i, l, br[b1]) tmp2[a[i]] = 0;
			rep(i, bl[b2], r) tmp2[a[i]] = 0;
			
			
			ans = (ans + P) % P;
		}
		cout << ans << "\n";
	}
	
	return 0;
}
