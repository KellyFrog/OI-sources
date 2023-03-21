// Problem: D - Half Reflector
// Contest: AtCoder - AtCoder Grand Contest 011
// URL: https://atcoder.jp/contests/agc011/tasks/agc011_d
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

const int N = 2e5 + 5;

int n, k;
char s[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> k >> (s+1);
	k = min(k, 4*n + (k%2));
	int c = 0;
	int pos = 1;
	rep(i, 1, k) {
		if(c && s[pos] == 'B') s[pos] = 'A';
		else if(!c && s[pos] == 'A') s[pos] = 'B';
		else {
			c ^= 1;
			pos = pos % n + 1;
		}
	}
	rep(i, 1, n) {
		if(c & 1) cout << char(s[pos] ^ 'A' ^ 'B');
		else cout << s[pos];
		pos = pos % n + 1;
	}
	cout << "\n";
	
	return 0;
}

