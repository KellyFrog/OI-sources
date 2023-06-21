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

int n, m;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> m;
	int l = 1, r = n;
	for(; l < r; ++l, --r) {
		rep(i, 1, m) {
			cout << l << " " << i << "\n";
			cout << r << " " << m-i+1 << "\n";
		}
	}
	if(l == r) {
		rep(i, 1, (m+1)/2) {
			cout << l << " " << i << "\n";
			if(i != m-i+1) cout << l << " " << m-i+1 << "\n";
		}
	}
	
	return 0;
}
