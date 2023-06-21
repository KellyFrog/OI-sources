#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pf push_front
#define rep(i, s, t) for (int i = s; i <= t; ++i)
#define per(i, s, t) for (int i = t; i >= s; --i)

const int N = 3e5 + 5;
const int base = 131;

int n;
char s[N];
ull h1[N], h2[N], pw[N];
int ans[N];

inline int geth1(int l, int r) {
	return h1[r] - h1[l-1] * pw[r-l+1];
}

inline int geth2(int l, int r) {
	return h2[l] - h2[r+1] * pw[r-l+1];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> (s+1);
	n = strlen(s+1);
	pw[0] = 1;
	rep(i, 1, n) pw[i] = pw[i-1] * base;
	rep(i, 1, n) h1[i] = h1[i-1] * base + s[i];
	per(i, 1, n) h2[i] = h2[i+1] * base + s[i];
	rep(i, 1, n) {
		int res = -1;
		rep(j, 2, min(i, n-i+1)) if(s[i] == s[i-j+1] && s[i] == s[i+j-1]) {
			res = j;
			break;
		}
		if(res != -1) ans[i+res-1] = max(ans[i+res-1], i-res+1);
	}
	ll res = 0;
	rep(i, 1, n) res += (ans[i] = max(ans[i], ans[i-1]));
	cout << res << "\n";
	
	return 0;
}
