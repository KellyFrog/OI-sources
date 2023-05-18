// Problem: AT1999 [AGC002E] Candy Piles
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT1999
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// Create Time: 2022-06-23 10:24:45
// Input/Output: stdin/stdout
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

int n, a[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n;
	rep(i, 1, n) cin >> a[i];
	sort(a + 1, a + n + 1, greater<int>());
	int p = 0;
	rep(i, 1, n-1) if(a[i+1] >= i+1) p = i;
	int d1 = a[p+1]- p;
	int d2 = 0;
	rep(i, 1, n) if(a[i] > p) d2 = i;
	d2 = d2 - p;

	cerr << p << " " << d1 << " " << d2 << "\n";
	d1 %= 2, d2 %= 2;
	if(d1 && d2) cout << "Second" << "\n";
	else cout << "First" << "\n";

	return 0;
}