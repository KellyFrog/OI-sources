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
int a[N], b[N], c[N];
int f[N][4];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n;
	rep(i, 1, n) {
		char ch; cin >> ch;
		c[i] = a[i] = ch - '0';
	}
	rep(i, 1, n) {
		char ch; cin >> ch;
		b[i] = ch - '0';
	}
	per(i, 1, n) a[i] ^= a[i-1];
	per(i, 1, n) b[i] ^= b[i-1];


	memset(f, 0x3f, sizeof f);
	f[0][0] = 0;
	f[1][1] = 2 + b[1];
	rep(i, 1, n) {
		f[i][0] = min(f[i][0], f[i-1][0] + (a[i] ^ b[i]));
		f[i][0] = min(f[i][0], f[i-1][1<<1-c[i]] + (1 ^ b[i]));
		f[i][1] = min(f[i][1], f[i-1][1] + b[i]);
		f[i][1] = min(f[i][1], f[i-1][3] + (1 ^ b[i]));
		f[i][1] = min(f[i][1], f[i-1][2] + 2 + (1 ^ b[i]));
		f[i][2] = min(f[i][2], f[i-1][2] + b[i]);
		f[i][2] = min(f[i][2], f[i-1][3] + (1 ^ b[i]));
		f[i][2] = min(f[i][2], f[i-1][1] + 2 + (1 ^ b[i]));
		f[i][3] = min(f[i][3], f[i-1][3] + b[i]);
		f[i][3] = min(f[i][3], min(f[i-1][1], f[i-1][2]) + 2 + b[i]);
		f[i][1<<1-c[i-1]] = min(f[i][1<<1-c[i-1]], f[i-1][0] + 2 + (1 ^ b[i]));
	}
	cout << (min({f[n][0], f[n][1], f[n][2], f[n][3]}) + 1 >> 1) << "\n";
	
	return 0;
}
