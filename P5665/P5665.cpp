#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
#define rg register
#define mp make_pair
#define pb push_back
#define pf push_front
#define fi first
#define se second
#define rep(i, s, t) for(rg int i = s; i <= t; i++)
#define per(i, s, t) for(rg int i = t; i >= s; i--)
#define debug(x) cerr << #x << "=" << x << "\n"

template<typename T>
void qread(T& x) {
	x = 0;
	rg char ch = ' ';
	int ps = 1;
	while(!isdigit(ch) && ch != '-') ch = getchar();
	if(ch == '-') ps = -1, ch = getchar();
	while(isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
	x *= ps;
}

template<typename T>
void qwrite(T x) {
	if(x < 0) putchar('-'), x = -x;
	if(x < 10) putchar('0' + x);
	else qwrite(x / 10), putchar('0' + (x % 10));
}

template<typename T>
void qwrite(T x, char ch) {
	qwrite(x), putchar(ch);
}

template<typename T>
void chkmin(T& x, T y) {
	if(x > y) x = y;
}

template<typename T>
void chkmax(T& x, T y) {
	if(x < y) x = y;
}

template<typename T>
void chkmod(T& x, ll mod) {
	return x > mod ? x - mod : x;
}

ll qpow(ll x, ll p, ll mod) {
	rg ll res = 1, base = x;
	while(p) {
		if(p & 1) res = (res * base) % mod;
		base = (base * base) % mod;
		p >>= 1;
	}
	return res;
}

const int N = 4e7 + 5;
const ll mod = (1 << 30);

int a[N], b[N], last[N], p[N], l[N], r[N];
__int128 sum[N], dp[N];
int que[N], head, tail;
int n, type, x, y, z, m;

int main() {
	qread(n), qread(type);
	if(type) {
		qread(x);
		qread(y);
		qread(z);
		qread(b[1]);
		qread(b[2]);
		qread(m);
		for(register int i = 1 ; i <= m ; i ++) {
			qread(p[i]);
			qread(l[i]);
			qread(r[i]);
		}
		for(register int i = 3 ; i <= n ; i ++) {
			b[i] = (0ll + 1ll * b[i - 1] * x + 1ll * b[i - 2] * y + z) % mod ;
		}
		for(register int i = 1 ; i <= m ; i ++)
			for(register int j = p[i - 1] + 1 ; j <= p[i] ; j ++) {
				a[j] = (b[j] % (r[i] - l[i] + 1)) + l[i] ;
			}
	} else {
		rep(i, 1, n) qread(a[i]);
	}
	cerr << "OK!" << endl;
	rep(i, 1, n) sum[i] = sum[i-1] + a[i];
	rep(i, 1, n) {
		while(head < tail && last[que[head+1]] + sum[que[head+1]] <= sum[i]) head++;
		rg int p = que[head];
		last[i] = sum[i] - sum[p], dp[i] = dp[p] + last[i] * last[i];
		while(head <= tail && last[que[tail]] + sum[que[tail]] >= last[i] + sum[i]) tail--;
		que[++tail] = i;
	}
	qwrite(dp[n], '\n');
	return 0;
}