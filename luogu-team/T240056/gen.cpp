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

mt19937 mtrnd(chrono::steady_clock::now().time_since_epoch().count());

const int N = 1e5 + 5;

int n, q;
int a[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	n = mtrnd() % 50 + 1, q = mtrnd() % 100 + 1;
	cout << n << " " << q << "\n";
	set<int> s;
	rep(i, 1, n) {
		int x;
		do {
			x = mtrnd() % (int)1e9 + 1;
		} while(s.count(x));
		s.insert(x);
		cout << x << " \n"[i == n];
	}
	while(q--) {
		int op = mtrnd() % 2 + 1;
		int l = mtrnd() % n + 1;
		int r = mtrnd() % n + 1;
		if(op == 1) l = 1, r = n;
		if(l > r) swap(l, r);
		cout << op << " " << l << " " << r << "\n";
	}
	
	return 0;
}
