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

mt19937_64 mtrnd(chrono::steady_clock::now().time_since_epoch().count());

const int N = 2.5e5 + 5;

int n, q;
int a[N], b[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	n = 2.5e5;
	q = 2.5e5;
	q = 5;
	cout << 0 << " " << n << "\n";
	rep(i, 1, n) a[i] = b[i] = i;
	rep(i, 1, n) cout << a[i] << " \n"[i == n];
	rep(i, 1, n) cout << b[i] << " \n"[i == n];
	cout << q << "\n";
	while(q--) {
		int l = mtrnd() % n + 1, r = mtrnd() % n + 1;
		if(l > r) swap(l, r);
		cout << l << " " << r << "\n";
	}
	
	return 0;
}
