// Problem: AT2165 [AGC006D] Median Pyramid Hard
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT2165
// Memory Limit: 250 MB
// Time Limit: 2000 ms
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

const int N = 2e5 + 5;

int n, a[N];
bool b[N];

bool check(int x) {
	rep(i, 1, 2*n-1) b[i] = a[i] >= x;
	int p1 = 0, p2 = 2 * n;
	per(i, 1, n-1) if(b[i] == b[i+1]) {
		p1 = i+1;
		break;
	}
	rep(i, n+1, 2*n-1) if(b[i] == b[i-1]) {
		p2 = i-1;
		break;
	}
	if(p1 == 0 && p2 == 2 * n) return (n & 1) ^ b[n] ^ 1;
	if(n - p1 < p2 - n) return b[p1];
	else return b[p2];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n;
	rep(i, 1, 2*n-1) cin >> a[i];
	
	int L = 1, R = 2 * n - 1;
	int res = 0;
	while(L <= R) {
		int mid = L + R >> 1;
		if(check(mid)) res = mid, L = mid + 1;
		else R = mid - 1;
	}
	cout << res << "\n";
	
	return 0;
}
