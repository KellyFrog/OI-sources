#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)
#define fi first
#define se second
#define mp make_pair
#define pb push_back

const int N = 1e6 + 5;

int n;
int a[N];
set<int> s1, s2, s3;

bool check() {
	s1.clear(), s2.clear(), s3.clear();
	rep(i, 1, n) {
		if(s1.count(a[i])) {
			return 0;
		}
		s1.emplace(a[i]);
		if(s2.count(i+a[i]) || s2.count(i+a[i]-n)) {
			return 0;
		}
		s2.emplace(i+a[i]);
		if(s3.count(i-a[i]) || s3.count(i-a[i]+n)) {
			return 0;
		}
		s3.emplace(i-a[i]);
	}
	return 1;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	cin >> n;

	rep(i, 1, n) a[i] = (2 * i - 1) % n + 1;
	if(check()) {
		rep(i, 1, n) cout << a[i] << " \n"[i == n];
		return 0;
	}

	rep(i, 1, n) a[i] = (2 * i + 1 - 1) % n + 1;
	if(check()) {
		rep(i, 1, n) cout << a[i] << " \n"[i == n];
		return 0;
	}

	rep(i, 1, n) a[i] = (2 * i + 2 - 1) % n + 1;
	if(check()) {
		rep(i, 1, n) cout << a[i] << " \n"[i == n];
		return 0;
	}

	cout << -1 << "\n";

	return 0;
}
