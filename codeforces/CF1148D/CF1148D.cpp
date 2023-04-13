// Problem: CF1148D Dirty Deeds Done Dirt Cheap
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1148D
// Memory Limit: 250 MB
// Time Limit: 3000 ms

/*
 * Author: chenkaifeng @BDFZ
 */

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

std::mt19937 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

const int N = 3e5 + 5;

int n;
int a[N], b[N];
vector<int> v1, v2;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n;
	rep(i, 1, n) {
		cin >> a[i] >> b[i];
		if(a[i] < b[i]) v1.pb(i);
		if(a[i] > b[i]) v2.pb(i);
	}
	sort(v1.begin(), v1.end(), [&](int x, int y) { return b[x] > b[y]; });
	sort(v2.begin(), v2.end(), [&](int x, int y) { return a[x] < a[y]; });
	
	if(v1.size() > v2.size()) {
		cout << v1.size() << "\n";
		for(int x : v1) cout << x << " "; cout << "\n";
	} else {
		cout << v2.size() << "\n";
		for(int x : v2) cout << x << " "; cout << "\n";
	}
	
	return 0;
}
