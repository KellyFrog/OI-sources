// Problem: AT2173 [AGC007F] Shik and Copying String
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT2173
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

const int N = 1e6 + 5;

int n;
char s[N], t[N];
int r[N], sum[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n;
	cin >> (s + 1) >> (t + 1);
	int p = n;
	per(i, 1, n) {
		p = min(p, i);
		while(p && s[p] != t[i]) --p;
		if(!p) break;
		r[p] = max(r[p], i);
	}
	if(!p) {
		cout << -1 << "\n";
		return 0;
	}
	if(strcmp(s+1, t+1) == 0) {
		cout << 0 << "\n";
		return 0;
	}
	rep(i, 1, n) if(r[i]) ++sum[i], --sum[r[i]+1];
	rep(i, 1, n) sum[i] += sum[i-1];
	int ans = 0;
	rep(i, 1, n) ans = max(ans, sum[i]);
	cout << ans << "\n";
	
	return 0;
}
