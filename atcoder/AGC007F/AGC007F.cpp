// Problem: AT_agc007_f [AGC007F] Shik and Copying String
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_agc007_f
// Memory Limit: 256 MB
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
int f[N], pos[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n;
	cin >> (s + 1) >> (t + 1);

	if(strcmp(s + 1, t + 1) == 0) {
		cout << 0 << "\n";
		return 0;
	}

	int p = n;
	per(i, 1, n) {
		p = min(p, i);
		while(p && s[p] != t[i]) --p;
		if(!p) {
			cout << -1 << "\n";
			return 0;
		}
		pos[i] = p;
	}
	queue<pair<int, int>> q;
	int d = 0, ans = 0;
	per(i, 1, n) {
		if(pos[i] == pos[i+1]) continue;
		--d;
		if(pos[i] != pos[i+1] - 1) q.emplace(pos[i] - d, 1 + d);
		while(!q.empty() && q.front().fi + d >= i) q.pop();
		if(!q.empty()) {
			ans = max(ans, q.front().se - d);
		}
	}
	cout << ans << "\n";

	
	return 0;
}

