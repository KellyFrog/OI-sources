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

int n, a[N], b[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n;
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, n) cin >> b[i];
	int p = find(b + 1, b + n + 1, 1) - b;
	priority_queue<int, vector<int>, greater<int>> pq;
	vector<int> v(b + p, b + n + 1);
	rep(i, 1, n) if(a[i]) pq.emplace(a[i]);
	bool ok = 1;
	rep(i, 1, p-1) {
		if(pq.empty()) {
			ok = 0;
			break;
		}
		if(pq.top() != n-p+1+i) {
			ok = 0;
			break;
		}
		v.pb(pq.top());
		pq.pop();
		if(b[i]) pq.emplace(b[i]);
	}
	ok &= pq.empty();
	if(v.size() == n) for(int i = 0; i < n; ++i) ok &= v[i] == i+1;
	if(ok) {
		cout << p-1 << "\n";
		return 0;
	}
	int mx = 0;
	rep(i, 1, n) if(b[i]) mx = max(mx, i - b[i]);
	cout << n + mx + 1 << "\n";
	
	return 0;
}
