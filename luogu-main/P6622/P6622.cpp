// Problem: P6622 [省选联考 2020 A/B 卷] 信号传递
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6622
// Memory Limit: 512 MB
// Time Limit: 3000 ms
// Create Time: 2022-02-24 16:10:19
// Input/Output: stdin/stdout
// 
// Powered by CP Editor (https://cpeditor.org)

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

// const int mod = 1e9 + 7;
const int mod = 998244353;

int qpow(int x, ll p) {
	int res = 1, base = x;
	while(p) {
		if(p & 1) res = 1ll * res * base % mod;
		base = 1ll * base * base % mod;
		p >>= 1;
	}
	return res;
}

template<typename T> inline void upd(T& x, const T& y) {	x += y;	if(x >= mod) x -= mod; }
template<typename T> inline void upd(T& x, const T& y, const T& z) { x = y + z; if(x >= mod) x -= mod; }

std::mt19937_64 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

/* template ends here */

const int M = 25;
const int C = 1 << 23 | 5;
const int CC = 1 << 13 | 5;
const int N = 1e5 + 5;

int n, m, k;
int p[N];
int cnt[M][M], cnt1[M][CC], cnt2[M][CC], cnt3[M][CC], cnt4[M][CC], tt[M];
ll f[C];
int popcount[C];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> m >> k;
	rep(i, 1, n) cin >> p[i], ++tt[p[i]];
	rep(i, 2, n) ++cnt[p[i-1]][p[i]];
	
	m = max(m, 8);
	
	int U = (1 << m) - 1;
	int low = U & ((1 << 12) - 1);
	int high = U >> 12;
	int t = 12;
	int u = (1 << t) - 1;
	
	rep(i, 1, m) rep(j, 1, m) {
		if(i != j) {
			if(j-1 < 12) cnt1[i][1<<j-1] = cnt[i][j], cnt3[i][1<<j-1] = cnt[j][i];
			else cnt2[i][1<<j-13] = cnt[i][j], cnt4[i][1<<j-13] = cnt[j][i];
		}
	}
	
	
	rep(i, 1, m) rep(S, 1, u) {
		cnt1[i][S] = cnt1[i][S&(S-1)] + cnt1[i][S^(S&(S-1))];
		cnt2[i][S] = cnt2[i][S&(S-1)] + cnt2[i][S^(S&(S-1))];
		// assert(tmp == cnt1[i][S]);
		cnt3[i][S] = cnt3[i][S&(S-1)] + cnt3[i][S^(S&(S-1))];
		cnt4[i][S] = cnt4[i][S&(S-1)] + cnt4[i][S^(S&(S-1))];
	}
	
	cerr << "ok" << "\n";
	
	auto getcnt1 = [&](int i, int s) {
		return cnt1[i][s&low] + cnt2[i][s>>12];
	};
	
	auto getcnt2 = [&](int i, int s) {
		return cnt3[i][s&low] + cnt4[i][s>>12];
	};
	
	rep(S, 1, U) popcount[S] = (S & 1) + popcount[S>>1];
	
	memset(f, 0x3f, sizeof f);
	f[0] = 0;
	rep(S, 0, U-2) {
		rep(i, 1, m) {
			if(S >> i-1 & 1) continue;
			// debug("add S = {}, i = {} to {}\n", S, i, S|1<<i-1);
			f[S|1<<i-1] = min(f[S|1<<i-1],
			f[S] 
			- 1ll * getcnt1(i, U^S^(1<<i-1)) * (popcount[S]+1)
			+ 1ll * getcnt2(i, S) * (popcount[S]+1)
			+ 1ll * k * (getcnt1(i, S) + getcnt2(i, U^S^(1<<i-1))) * (popcount[S] + 1));
			
		}
	}
	
	cout << f[U] << "\n";
	
	return 0;
}
