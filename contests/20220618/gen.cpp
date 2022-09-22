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

mt19937_64 mtrnd(chrono::system_clock::now().time_since_epoch().count());

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	int t = 1e5;
	cout << t << "\n";
	while(t--) {
		int n = mtrnd() % 7 + 1;
		vector<int> a(n), b(n);
		for(int i = 0; i < n; ++i) a[i] = b[i] = i+1;
		shuffle(a.begin(), a.end(), mtrnd);
		shuffle(b.begin(), b.end(), mtrnd);
		cout << n << " " << mtrnd() % n + 1 << "\n";
		for(int x : a) cout << x << " " ; cout << "\n";
		for(int x : b) cout << x << " " ; cout << "\n";
		
	}
	
	return 0;
}