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

std::mt19937_64 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

const int N = 1e3 + 5;
const int K = 5e6 + 5;

long double p[N][N];
long double prep[N], preval[N];
int n, k;

int main() {
	freopen("camp.in", "r", stdin);
	freopen("camp.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	
	cin >> n >> k;
	--n;
	p[0][0] = 1;
	rep(i, 1, n) rep(j, 0, i) {
		if(j) p[i][j] = (p[i-1][j-1] + p[i-1][j]) / 2;
		else p[i][j] = p[i-1][j] / 2;
	}
	
	prep[0] = p[n][0];
	rep(i, 1, n) prep[i] = prep[i-1] + p[n][i];
	
	preval[0] = 0;
	rep(i, 1, n) preval[i] = p[n][i] * i + preval[i-1];
	
	long double last = (long double)n / 2;
	rep(i, 2, k) {
		int pos = int(ceil(last));
		last = prep[pos-1] * last + preval[n] - preval[pos-1];
	}

	cout << last+1 << endl;
	
	return 0;
}
