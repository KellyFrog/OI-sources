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

const int N = 4.3e4 + 4;

int f[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	memset(f, 0x3f, sizeof f);

	int n = 43000;
	f[0] = f[1] = 0;
	f[2] = 2;
	rep(i, 3, n) {
		rep(j, 1, i-1) f[i] = min(f[i], i + j + f[j] + f[i-j] - 1) ;
	}

	cout << f[n] + 2 * n << "\n";

	return 0;
}
