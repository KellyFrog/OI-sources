
// Problem: T115642 棋盘问题
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T115642?contestId=38854
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

//Author: Chenkaifeng

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define fi first
#define se second
#define rg register
#define mp make_pair
#define pb push_back
#define pf push_front

#define rep(i, s, t) for(rg int i = s; i <= t; i++)
#define per(i, s, t) for(rg int i = t; i >= s; i--)
#define debug(x) cerr << (#x) << " = " << (x) << "\n"
#define OK cerr << "OK!\n"

inline void qread() {}
template<typename T1, typename ...T2>
inline void qread(T1 &x, T2&... ls) {
	x = 0;
	rg char ch = ' '; rg int ps = 1;
	while(!isdigit(ch) && ch != '-') ch = getchar();
	if(ch == '-') ps = -1, ch = getchar();
	while(isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
	x *= ps;
	qread(ls...);
}

template<typename T>
inline void qwrite(T x) {
	if(x < 0) putchar('-'), x = -x;
	if(x < 10) return putchar('0' + x), void();
	qwrite(x / 10), putchar('0' + (x % 10));
}

template<typename T>
inline void qwrite(T x, char ch) {
	qwrite(x), putchar(ch);
}

ll qpow(ll x, ll p, ll mod) {
	rg ll base = x, res = 1;
	while(p) {
		if(p & 1) res = (res * base) % mod;
		base = (base * base) % mod;
		p >>= 1;
	}
	return res;
}

const int N = 9;
const int M = 1 << N;

#define popcount __builtin_popcount

int n, k;
int dp[N][M], base[N];
char str[N];

int main() {
	while(cin >> n >> k) {
		memset(dp, 0, sizeof dp);
		memset(base, 0, sizeof base);
		if(n == -1) return 0;
		rep(i, 1, n) {
			cin >> str;
			rep(j, 0, n-1) base[i] |= (str[j] == '.') << j;
		}
		dp[0][0] = 1;
		int lim = (1 << n) - 1;
		rep(i, 1, n) {
			//dp[i][0] = 1;
			rep(j, 0, n-1) {
				if((base[i] & (1 << j)) == 0) {
					rep(k, 1, lim) {
						if(k & (1 << j)) dp[i][k] += dp[i-1][k ^ (1 << j)];
					}
				}
			}
			rep(j, 0, lim) dp[i][j] += dp[i-1][j];
		}
		int ans = 0;
		rep(j, 0, lim) if(popcount(j) == k) ans += dp[n][j];
		cout << ans << endl;
	}
	return 0;
}
