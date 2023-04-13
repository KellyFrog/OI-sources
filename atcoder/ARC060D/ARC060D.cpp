// Problem: F - Best Representation
// Contest: AtCoder - AtCoder Regular Contest 060
// URL: https://atcoder.jp/contests/arc060/tasks/arc060_d
// Memory Limit: 256 MB
// Time Limit: 2000 ms

/*
 * Author: chenkaifeng @BDFZ
 */
 
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

/* template ends here */

std::mt19937 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

const int N = 5e5 + 5;

int n;
char s[N], t[N];
int nxt[N], tnxt[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> (s+1);
	n = strlen(s+1);
	
	rep(i, 1, n) t[i] = s[n-i+1];
	
	nxt[1] = 0;
	rep(i, 2, n) {
		int p = nxt[i-1];
		while(p && s[p+1] != s[i]) p = nxt[p];
		if(s[p+1] == s[i]) ++p;
		nxt[i] = p;
	}
	
	tnxt[1] = 0;
	rep(i, 2, n) {
		int p = tnxt[i-1];
		while(p && t[p+1] != t[i]) p = tnxt[p];
		if(t[p+1] == t[i]) ++p;
		tnxt[i] = p;
	}
	
	if(nxt[n] == 0) {
		cout << 1 << "\n" << 1 << "\n";
		return 0;
	}
	
	if(n % (n - nxt[n]) == 0) {
		if(nxt[n] == n-1) {
			cout << n << "\n" << 1 << "\n";
		} else {
			int res = 0;
			rep(i, 2, n) {
				auto check1 = [&](int x) {
					return !nxt[x] || x%(x-nxt[x]) != 0;
				};
				
				auto check2 = [&](int x) {
					return !tnxt[x] || x%(x-tnxt[x]) != 0;
				};
				
				if(check1(i-1) && check2(n-i+1)) ++res;
			}
			cout << 2 << "\n";
			cout << res << "\n";
		}
	} else {
		cout << 1 << "\n" << 1 << "\n";
	}
	
	return 0;
}
