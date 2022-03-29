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

// const int P = 2;
const int P = 998244353;

inline int emod(ll x, int P) {
	return x > 2*P ? x % P + P : x;
}

int qpow(int x, ll p, int P) {
	if(p < 0) return 1;
	p = emod(p, P);
	int res = 1, base = x;
	while(p) {
		if(p & 1) res = emod(1ll * res * base, P);
		base = emod(1ll * base * base, P);
		p >>= 1;
	}
	return res;
}

mt19937_64 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

const int N = 3e4 + 5;

int n, a[N], f[N], suf[N];
vector<int> phi;
int pw[N];

int main() {
	freopen("zote.in", "r", stdin);
	freopen("zote.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n;
	rep(i, 1, n) cin >> a[i];
	
	int p0 = P;
	phi.pb(p0);
	while(p0 != 1) {
		auto getphi = [&](int p) {
			int ret = p;
			int pp = p;
			for(int i = 2; i * i <= p; ++i) {
				if(pp % i == 0) {
					ret /= i;
					ret *= (i-1);
					while(pp % i == 0) pp /= i;
				}
			}
			if(pp > 1) {
				ret /= pp;
				ret *= pp-1;
			}
			return ret;
		};
		phi.pb(p0 = getphi(p0));
	}
	phi.pb(1);
	
	pw[0] = 1;
	rep(i, 1, n) pw[i] = 2ll * pw[i-1] % P;
	
	per(i, 1, n) {
		int x = 0;
		for(int j = 0; j < phi.size(); ++j) {
			if(i + j > n) break;
			
			auto calc = [&](int l, int r, int len) {
				int res = emod(a[r], phi[len]);
				per(i, 0, len-1) {
					res = qpow(a[l+i], res, phi[i]);
				}
				return res;
			};
			
			x = calc(i, i+j, j) % P;
			f[i] = (f[i] + 1ll * x * (n-i-j-1 < 0 ? 1 : pw[n-i-j-1]) + f[i+j+1]) % P;
		}
		if(i + phi.size() <= n) {
			int p = i + phi.size() + 1;
			int len = n - p + 1;
			if(len == 0) {
				f[i] = (f[i] + x) % P;
			} else {
				f[i] = (f[i] + 1ll * x * pw[len] + suf[p]) % P;
			}
		}
		suf[i] = (suf[i+1] + f[i]) % P;
	}
	
	cout << f[1] << endl;
	
	return 0;
}

