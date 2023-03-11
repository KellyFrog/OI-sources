
// Problem: D - Piling Up
// Contest: AtCoder - AtCoder Grand Contest 013
// URL: https://atcoder.jp/contests/agc013/tasks/agc013_d
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

const int N = 3e3 + 5;
const int P = 1e9 + 7;

int n, m;
int f[N][N][2];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> m;
	rep(i, 0, n) f[0][i][i==0] = 1;
	rep(i, 1, m) {
		rep(j, 0, n) {
			if(j >= 1) {
				f[i][j][0] = (f[i][j][0] + f[i-1][j-1][0]) % P;
				f[i][j][1] = (f[i][j][1] + f[i-1][j-1][1]) % P;
				f[i][j][j==1] = (f[i][j][j==1] + f[i-1][j][0]) % P;
				f[i][j][1] = (f[i][j][1] + f[i-1][j][1]) % P;
			}
			if(j < n) {
				f[i][j][0] = (f[i][j][0] + f[i-1][j+1][0]) % P;
				f[i][j][1] = (f[i][j][1] + f[i-1][j+1][1]) % P;
				f[i][j][0] = (f[i][j][0] + f[i-1][j][0]) % P;
				f[i][j][1] = (f[i][j][1] + f[i-1][j][1]) % P;
			}
		}
		f[i][0][1] = (f[i][0][1] + f[i][0][0]) % P;
		f[i][0][0] = 0;
	}
	int ans = 0;
	rep(i, 0, n) ans = (ans + f[m][i][1]) % P;
	cout << ans << "\n";
	
	return 0;
}
