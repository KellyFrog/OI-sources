// Problem: U221772 LCM之美
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/U221772?contestId=71542
// Memory Limit: 512 MB
// Time Limit: 5000 ms
// Create Time: 2022-06-11 15:46:40
// Input/Output: stdin/stdout
// 
// Powered by CP Editor (https://cpeditor.org)

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

const int N = 1e7 + 5;
const int P = 998244353;

int n, k, T;
bool vis[N];
int mu[N], pre[N];
int res[N];
unordered_map<int, int> pr;

int qpow(int x, ll p) {
	int res = 1, base = x;
	while(p) {
		if(p & 1) res = 1ll * res * base % P;
		base = 1ll * base * base % P;
		p >>= 1;
	}
	return res;
}

namespace sub1 {
const int inv = qpow(6, P - 2);

void init(int n) {
	mu[1] = 1;
	rep(i, 2, n) {
		if(!vis[i]) {
			mu[i] = -1;
			for(int j = i + i; j <= n; j += i) {
				vis[j] = 1;
				if((j / i) % i == 0) mu[j] = 0;
				else mu[j] = -mu[j / i];
			}
		}
	}
	rep(i, 1, n) mu[i] = 1ll * mu[i] * i % P * i % P;
	rep(i, 1, n) pre[i] = (pre[i-1] + mu[i]) % P;
}

int spre(int n) {
	return 1ll * n * (n + 1) % P * (2 * n + 1) % P * inv % P;
}

int cnt = 0;

int calc(int n) {
	if(n <= (int)1e7) return pre[n];
	if(pr.count(n)) return pr[n];
	int ans = 1;
	for(int l = 2, r = 0; l <= n; l = r + 1) {
		r = n / (n / l);
		ans = (ans - 1ll * (spre(r) - spre(l-1)) * calc(n / l)) % P;
	}
	return pr[n] = ans;
}

void solve() {
	cin >> n;
	
	int ans = 0;
	
	auto getans = [&](int k) {
		int x = (1ll * k * (k+1) / 2) % P;
		return 1ll * x * x % P;
	};
	
	for(int l1 = 1, r1 = 0; l1 <= n; l1 = r1 + 1) {
		r1 = n / (n / l1);
		int m = n / l1;
		int prem = calc(r1) - calc(l1 - 1);
		int res = 0;
		if(m <= (int)1e7 && ::res[m] != 0) res = ::res[m];
		else {
			for(int l2 = 1, r2 = 0; l2 <= m; l2 = r2 + 1) {
				r2 = m / (m / l2);
				int sum = 1ll * (l2 + r2) * (r2 - l2 + 1) / 2 % P;
				res = (res + 1ll * sum * getans(m / l2)) % P;
			}
			if(m <= (int)1e7) ::res[m] = res;
		}
		ans = (ans + 1ll * prem * res) % P;
	}
	cout << (ans + P) % P << "\n";
}

void main() {
	init(1e7);
	while(T--) solve();
}

}

namespace sub2 {
	
const int inv6 = qpow(6, P - 2);
const int inv30 = qpow(30, P - 2);


void init(int n) {
	mu[1] = 1;
	rep(i, 2, n) {
		if(!vis[i]) {
			mu[i] = -1;
			for(int j = i + i; j <= n; j += i) {
				vis[j] = 1;
				if((j / i) % i == 0) mu[j] = 0;
				else mu[j] = -mu[j / i];
			}
		}
	}
	rep(i, 1, n) rep(j, 1, 4) mu[i] = 1ll * mu[i] * i % P;
	rep(i, 1, n) pre[i] = (pre[i-1] + mu[i]) % P;
}

int sum2(int k) {
	return 1ll * k * (k + 1) % P * (2 * k + 1) % P * inv6 % P;
}

int sum4(int k) {
	return 1ll * k * (k + 1) % P * (2 * k + 1) % P * ((3ll * k * k + 3ll * k - 1) % P) % P * inv30 % P;
}

int calc(int n) {
	if(n <= (int)1e7) return pre[n];
	if(pr.count(n)) return pr[n];
	int ans = 1;
	for(int l = 2, r = 0; l <= n; l = r + 1) {
		r = n / (n / l);
		ans = (ans - 1ll * (sum4(r) - sum4(l-1)) * calc(n / l)) % P;
	}
	return pr[n] = ans;
}

void solve() {
	cin >> n;
	
	int ans = 0;
	
	for(int l1 = 1, r1 = 0; l1 <= n; l1 = r1 + 1) {
		r1 = n / (n / l1);
		int m = n / l1;
		int prem = calc(r1) - calc(l1 - 1);
		int res = 0;
		if(m <= (int)1e7 && ::res[m] != 0) res = ::res[m];
		else {
			for(int l2 = 1, r2 = 0; l2 <= m; l2 = r2 + 1) {
				r2 = m / (m / l2);
				int sum = sum2(r2) - sum2(l2 - 1);
				int s2 = sum2(m / l2); s2 = 1ll * s2 * s2 % P;
				res = (res + 1ll * sum * s2) % P;
			}
			if(m <= (int)1e7) ::res[m] = res;
		}
		ans = (ans + 1ll * res * prem) % P;
	}
	cout << (ans + P) % P << "\n";
}

void main() {
	init(1e7);
	
	while(T--) solve();
}
	
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	
	cin >> T >> k;
	
	if(k == 1) {
		sub1::main();
	} else {
		sub2::main();
	}
		
	
	return 0;
}