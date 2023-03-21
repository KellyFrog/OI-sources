// Problem: P7738 [NOI2021] 量子通信
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7738
// Memory Limit: 384 MB
// Time Limit: 2000 ms
// Create Time: 2022-05-28 16:24:53
// Input/Output: stdin/stdout
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

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

/* template ends here */

mt19937_64 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

const int N = 4e5 + 5;
const int M = 1 << 16 | 5;

int n, q;
ull a1, a2;
bitset<257> s[N], t;
int a[N];
vector<int> pos[18][M];

ull myRand(ull &k1, ull &k2) {
    ull k3 = k1, k4 = k2;
    k1 = k4;
    k3 ^= (k3 << 23);
    k2 = k3 ^ k4 ^ (k3 >> 17) ^ (k4 >> 26);
    return k2 + k4;
}

void gen(int n, ull a1, ull a2) {
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= 256; j++)
            s[i][a[j]] = (myRand(a1, a2) & (1ull << 32)) ? 1 : 0;
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> q >> a1 >> a2;
	rep(i, 1, 256) a[i] = i;
	shuffle(a + 1, a + 256 + 1, mtrnd);
	gen(n, a1, a2);

	rep(i, 1, n) {
		rep(k, 1, 16) {
			int x = 0;
			int st = (k-1) * 16 + 1;
			int ed = k * 16;
			rep(j, st, ed) x = x << 1 | s[i][j];
			pos[k][x].pb(i);
		}
	}

	bool lastans = 0;
	while(q--) {
		int kk;
		string str; cin >> str >> kk;
		assert(str.length() == 64);
		rep(i, 0, 63) {
			int st = i * 4 + 1, ed = (i + 1) * 4;
			int val = isdigit(str[i]) ? str[i] - '0' : str[i] - 'A' + 10;
			per(j, st, ed) {
				t[a[j]] = val & 1;
				val >>= 1;
			}
		}

		rep(i, 1, 256) if(lastans) t[i] = !t[i];

		bool ok = 0;

		rep(k, 1, 16) {
			int x = 0;
			int st = (k-1) * 16 + 1, ed = k * 16;
			rep(j, st, ed) x = x << 1 | t[j];
			for(int o : pos[k][x]) {
				if((s[o] ^ t).count() <= kk) {
					ok = 1;
					break;
				}
			}
			if(ok) break;
		}

		cout << (lastans = ok) << "\n";
	}
	
	return 0;
}