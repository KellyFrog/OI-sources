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

int f[N][3];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	memset(f, 0x3f, sizeof f);

	int n = 43000;
	f[0][0] = f[0][1] = f[0][2] = 0;
	f[1][0] = f[1][1] = f[1][2] = 0;
	f[2][0] = f[2][1] = f[2][2] = 1;
	rep(i, 3, n) {
		rep(j, 1, i-1) {
			f[i][0] = min(f[i][0], i+j+f[j][2]+f[i-j][1]);
			f[i][1] = min(f[i][1], i-j+i+f[j][2]+f[i-j][1]);
			f[i][2] = min(f[i][2], i-j+i+f[j][1]+f[i-j][0]);
		}
		if(i <= 50) cerr << i << " " << f[i][0] << " " << f[i][1] << " " << f[i][2] << "\n";
	}

	cout << min({f[n][0], f[n][1], f[n][2]}) + 2 * n << "\n";

	return 0;
}
