// Problem: E - Increasing Numbers
// Contest: AtCoder - AtCoder Grand Contest 011
// URL: https://atcoder.jp/contests/agc011/tasks/agc011_e
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

const int N = 5.1e5 + 5;

int n;
char s[N];
int a[N], cnt[15];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> (s+1);
	n = strlen(s+1);
	reverse(s+1, s+n+1);
	rep(i, 1, n) a[i] = s[i] - '0';
	bool f = 1;
	rep(i, 1, n) if(a[i] != 1) f = 0;
	if(f) {
		cout << 1 << "\n";
		return 0;
	}
	rep(i, 1, n) a[i] *= 9;
	rep(i, 1, n) {
		a[i+1] += a[i]/10;
		a[i] %= 10;
	}
	while(a[n+1]) {
		++n;
		a[n+1] = a[n] / 10;
		a[n] %= 10;
	}
	rep(i, 1, n) ++cnt[a[i]];
	int ans = 0;
	per(i, 1, n) {
		if(cnt[9] == i) {
			++ans;
			break;
		}
		
		ans += a[i];
		--cnt[a[1]];
		--cnt[a[i]];
		a[1] += a[i];
		a[i] = 0;
		rep(j, 1, n) {
			if(a[j] < 10) {
				++cnt[a[j]];
				break;
			}
			--cnt[a[j+1]];
			a[j+1] += a[j]/10;
			a[j] %= 10;
			++cnt[a[j]];
		}
	}
	cout << (ans+8)/9 << "\n";

	return 0;
}

