// Problem: E - Placing Squares
// Contest: AtCoder - AtCoder Grand Contest 013
// URL: https://atcoder.jp/contests/agc013/tasks/agc013_e
// Memory Limit: 256 MB
// Time Limit: 3000 ms
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

const int N = 1e5 + 5;
const int M = 35;
const int P = 1e9 + 7;

int n, m;
int a[N];
int base[M][4][4], vec[4], tmp[4];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> m;
	vector<int> v;
	rep(i, 1, m) cin >> a[i];
	base[0][0][0] = base[0][3][0] = 1;
	base[0][0][1] = base[0][3][1] = base[0][1][1] = 1;
	base[0][0][2] = base[0][3][2] = base[0][2][2] = 1;
	base[0][0][3] = base[0][1][3] = base[0][2][3] = 1, base[0][3][3] = 2;
	rep(t, 1, 30) {
		rep(i, 0, 3) rep(k, 0, 3) rep(j, 0, 3) base[t][i][j] = (base[t][i][j] + 1ll * base[t-1][i][k] * base[t-1][k][j]) % P;
	}
	vec[0] = 1;
	a[0] = -1;
	rep(i, 1, m) {
		int d = a[i] - a[i-1] - 1;
		rep(t, 0, 30) if(d >> t & 1) {
			memcpy(tmp, vec, sizeof tmp);
			memset(vec, 0, sizeof vec);
			rep(i, 0, 3) rep(j, 0, 3) vec[j] = (vec[j] + 1ll * tmp[i] * base[t][i][j]) % P;
		}
		vec[3] = ((ll)vec[0] + vec[1] + vec[2] + vec[3]) % P;
		vec[2] = (vec[0] + vec[2]) % P;
		vec[1] = (vec[0] + vec[1]) % P;
	}
	int d = n-1 - a[m];
	rep(t, 0, 30) if(d >> t & 1) {
		memcpy(tmp, vec, sizeof tmp);
		memset(vec, 0, sizeof vec);
		rep(i, 0, 3) rep(j, 0, 3) vec[j] = (vec[j] + 1ll * tmp[i] * base[t][i][j]) % P;
	}
	cout << vec[3] << "\n";

	return 0;
}

