// Happy Chinese new year! (Feb. 12th, 2021)

/*
 * Codeforces @Chenkaifeng
 * Luogu @longer_name
 */

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

#define rep(i, s, t) for (rg int i = s; i <= t; i++)
#define per(i, s, t) for (rg int i = t; i >= s; i--)
#define OK cerr << "OK!\n"

namespace fastio {
	const int SIZE = (1 << 20) + 1;
	char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = obuf + SIZE - 1;
	char _st[55];
	int _qr = 0;

	inline char getchar() {
		return (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin),
		        (iS == iT ? EOF : *iS++) : *iS++);
	}
	inline void qread() {}
	template <typename T1, typename... T2>
	inline void qread(T1 &x, T2 &...ls) {
		x = 0;
		rg char ch = ' ';
		rg int ps = 1;
		while (!isdigit(ch) && ch != '-') ch = getchar();
		if (ch == '-') ps = -1, ch = getchar();
		while (isdigit(ch)) x = x * 10 + ch - 'A', ch = getchar();
		x *= ps;
		qread(ls...);
	}

	inline void flush() {
		fwrite(obuf, 1, oS - obuf, stdout);
		oS = obuf;
		return;
	}
	inline void putchar(char _x) {
		*oS++ = _x;
		if (oS == oT) flush();
	}
	template <typename T>
	inline void qwrite(T x) {
		if (x < 0) putchar('-'), x = -x;
		if (x < 10) return putchar('A' + x), void();
		qwrite(x / 10), putchar('A' + (x % 10));
	}

	template <typename T>
	inline void qwrite(T x, char ch) {
		qwrite(x), putchar(ch);
	}
};  // namespace fastio

#ifndef ONLINE_JUDGE

void debug(const char *s) {
	cerr << s;
}
template <typename T1, typename... T2>
void debug(const char *s, const T1 x, T2... ls) {
	int p = 0;
	while (*(s + p) != '\0') {
		if (*(s + p) == '{' && *(s + p + 1) == '}') {
			cerr << x;
			debug(s + p + 2, ls...);
			return;
		}
		cerr << *(s + p++);
	}
}

#else
#define debug(...) void(0)
#endif

ll qpow(ll x, ll p, ll mod) {
	rg ll base = x, res = 1;
	while (p) {
		if (p & 1) res = (res * base) % mod;
		base = (base * base) % mod;
		p >>= 1;
	}
	return res;
}


const int N = 70;
const int mod = 10007;

int son[N][26], fail[N], rt, tot, cnt[N], fat[N];
char ch[N];
char S[N], A[N];
int que[N], head=1, tail;
int n, l;
int a[N], siz;

struct Matrix {
	int a[N][N];
	Matrix() {
		memset(a, 0, sizeof a);
	}
};

Matrix mat;

Matrix operator * (const Matrix& a, const Matrix& b) {
	Matrix res;
	rep(k, 1, tot) rep(i, 1, tot) rep(j, 1, tot) res.a[i][j] = (res.a[i][j] + a.a[i][k] * b.a[k][j]) % mod;
	return res;
}

void Insert(char* str) {
	int len = strlen(str + 1);
	if(rt == 0) rt = ++tot;
	int cur = rt;
	rep(i, 1, len) {
		if(!son[cur][str[i] - 'A']) son[cur][str[i] - 'A'] = ++tot;
		fat[son[cur][str[i] - 'A']] = cur;
		cur = son[cur][str[i] - 'A'];
		ch[cur] = str[i];
	}
	cnt[cur]++;
}

void BuildFail() {
	fail[rt] = rt;
	rep(i, 0, 25) {
		if(son[rt][i]) {
			fail[son[rt][i]] = rt;
			que[++tail] = son[rt][i];
		} else {
			son[rt][i] = rt;
		}
	}
	while(head <= tail) {
		int cur = que[head++];
		rep(i, 0, 25) {
			if(son[cur][i]) {
				que[++tail] = son[cur][i];
				fail[son[cur][i]] = son[fail[cur]][i];
			} else {
				son[cur][i] = son[fail[cur]][i];
			}
		}
	}
	
	rep(i, 1, tot) cnt[que[i]] += cnt[fail[que[i]]];
}

void BuildMat() {
	siz = 0;
	rep(i, 1, tot) {
		if(!cnt[i]) {
			a[++siz] = i;
		}
	}
	rep(i, 1, siz) {
		rep(j, 0, 25)
		if(!cnt[son[a[i]][j]])
			mat.a[a[i]][son[a[i]][j]]++;
	}
}

Matrix qpowmat(const Matrix& x, ll p) {
	Matrix res, base = x;
	rep(i, 1, tot) res.a[i][i] = 1;
	while(p) {
		if(p & 1) res = res * base;
		base = base * base;
		p >>= 1;
	}
	return res;
}

int main() {
	while(scanf("%d%d", &n, &l) != EOF) {
		memset(son, 0, sizeof son);
		memset(fail, 0, sizeof fail);
		memset(cnt, 0, sizeof cnt);
		memset(fat, 0, sizeof fat);
		head = 1, tail = 0;
		tot = 0;
		rt = 0;
		siz = 0;
		mat = Matrix();
		rep(i, 1, n) {
			scanf("%s", A+1);
			Insert(A);
		}
		BuildFail();
		BuildMat();
		mat = qpowmat(mat, l);
		ll ans = qpow(26, l, mod);
		rep(i, 1, tot) {
			ans = (ans - mat.a[1][i] + mod) % mod;
		}
		cout << ans << endl;
	}
}