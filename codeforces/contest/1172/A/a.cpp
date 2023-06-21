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

const int N = 4e5 + 5;

int n, a[N], b[N], pos[N];

int check(int k) {
	priority_queue<int, vector<int>, greater<int>> pq;
	rep(i, 1, min(k, n)) pq.emplace(b[i]);
	rep(i, 1, n) pq.emplace(a[i]);
	vector<int> v;
	rep(i, 1, n) {
		v.pb(pq.top()); pq.pop();
		pq.emplace(b[k+i]);
	}
	for(int i = 0; i < n; ++i) if(v[i] != i+1) return -1;
	return k+n;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n;
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, n) cin >> b[i];
	int L = 0, R = n;
	int res = -1;
	while(L <= R) {
		int mid = L + R >> 1;
		int res = check(mid);
		if(res != -1) R = mid - 1;
		else L = mid + 1;
	}
	cout << res << "\n";
	
	return 0;
}
