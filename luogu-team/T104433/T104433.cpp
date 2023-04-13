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

struct bigint {
	const ll base = 1e17;
	const int len = 15;
	ll num[5];
	bigint() {
		memset(num, 0, sizeof num);
	}
	ll& operator [](const int& p) {
		return num[p];
	}
	ll& size() {
		return num[0];
	}
	void operator = (const ll& x) {
		return num[num[0] = 1] = x, void();
	}
	void operator = (const bigint& x) {
		memcpy(num, x.num, sizeof x.num);
	}
	bigint operator + (bigint& x) {
		bigint res;
		res.size() = max(size(), x.size());
		rep(i, 1, res.num[0]) res[i] = num[i] + x[i];
		rep(i, 1, res.num[0]) res[i+1] += res[i] / base, res[i] %= base;
		if(res[res.size() + 1]) ++res.size();
		return res;
	}
	bigint operator + (const ll& p) {
		bigint res, x;
		x = p;
		res.size() = max(size(), x.size());
		rep(i, 1, res.num[0]) res[i] = num[i] + x[i];
		rep(i, 1, res.num[0]) res[i+1] += res[i] / base, res[i] %= base;
		if(res[res.size() + 1]) ++res.size();
		return res;
	}
	bigint operator - (const ll& x) {
		bigint res; res = *this;
		res[1] -= x;
		rep(i, 1, res.size()) if(res[i] < 0) res[i] += base, res[i+1]--;
		if(res[res.size()] == 0) --res.size();
		return res;
	}
		
	void read() {
		rg char ch = ' ';
		while(!isdigit(ch)) ch = getchar();
		while(isdigit(ch)) {
			rep(i, 1, size()) num[i] *= 10;
			num[1] += ch - '0';
			rep(i, 1, size()) num[i+1] += num[i] / base, num[i] %= base;
			if(num[size() + 1]) ++size();
			ch = getchar();
		}
	}
	int sum() {
		int res = 0;
		rep(i, 1, size()) res = (res + num[i]) % 3;
		return res;
	}
	bigint operator / (const ll& x) {
		bigint res;
		res = *this;
		per(i, 1, res.size()) {
			res[i-1] += (res[i] % x) * base;
			res[i] /= x;
		}
		while(res[res.size()] == 0 && size() > 0) --res.size();
		return res;
	}
	void write() {
		printf("%lld", num[num[0]]);
		per(i, 1, num[0] - 1) printf("%017lld", num[i]);
		puts("");
	}
	bool operator == (const ll& x) {
		return x == 0 ? size() == 0 : size() == 1 && num[1] == x;
	}
	ull gethash() {
		ull base = 131, res = 0;
		rep(i, 1, size()) res = (ull)(res * base) + num[i], base = base * 131;
		return res;
	}
};

bool operator < (bigint x, bigint y) {
	rep(i, 1, max(x.size(), y.size())) if(x[i] != y[i]) return x[i] < y[i];
	return 0;
}

const ll inf = 1e9;

map<bigint, int> m;

ll mi = (int)1e18;

ll Solve(bigint x, ll stp = 0) {
	//x.write();
	if(m.count(x)) return mi = min(mi, stp + m[x]), m[x];
	if(stp > mi) return inf;
	if(x == 2) return mi = min(mi, stp + 1), 1;
	if(x == 1) return mi = min(mi, stp), 0;
	if(x == 0) return inf;
	rg int sm = x.sum();
	if(sm == 0) return m[x] = Solve(x / 3, stp + 1) + 1;
	rg ll ans1 = Solve(x - sm, stp + sm) + sm;
	rg ll ans2 = Solve(x  + (3 - sm), stp + 3 - sm) + 3 - sm;
	m[x] = min(ans1, ans2);
}

int main() {
	bigint x;
	x.read();
	Solve(x);
	cout << mi << endl;
	return 0;
}
