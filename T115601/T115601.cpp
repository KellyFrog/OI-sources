
// Problem: T115601 围棋
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T115601?contestId=38854
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

const int N = 105;

char ch[N][N];
int n;
int fa[N * N], clr[N * N];

int Find(int x) {
	return x == fa[x] ? x : fa[x] = Find(fa[x]);
}

int id(int x, int y) {
	return x * n + y;
}

void Merge(int x, int y) {
	fa[Find(x)] = Find(y);
}

void Modify(int x, int y, int c) {
	if(ch[x][y] == '.') clr[Find(id(x, y))] = c;
}

int main() {
	cin >> n;
	rep(i, 1, n) cin >> ch[i] + 1;
	rep(i, 1, n * (n + 1)) fa[i] = i;
	rep(i, 1, n) rep(j, 1, n-1) {
		if(ch[i][j] == ch[i][j+1] && ch[i][j] == '.') Merge(id(i, j), id(i, j+1));
		if(ch[i][j] == ch[i-1][j] && ch[i][j] == '.') Merge(id(i, j), id(i-1, j));
	}
	int ans1 = 0, ans2 = 0;
	rep(i, 1, n) rep(j, 1, n) {
		if(ch[i][j] != '.') {
			Modify(i - 1, j, ch[i][j] == 'B');
			Modify(i + 1, j, ch[i][j] == 'B');
			Modify(i, j - 1, ch[i][j] == 'B');
			Modify(i, j + 1, ch[i][j] == 'B');
		}
	}
	rep(i, 1, n) rep(j, 1, n) {
		if(ch[i][j] == '.') {
			if(clr[Find(id(i, j))] == 1) ans1++;
			else ans2++;
		} else {
			if(ch[i][j] == 'B') ans1++;
			else ans2++;
		}
	}
	cout << ans1 << " " << ans2 << endl;
	return 0;
}
