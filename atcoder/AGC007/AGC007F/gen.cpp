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

char s[100000];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);


	int n = 10;
	cout << n << "\n";
	rep(i, 1, n) s[i] = char('a' + mtrnd() % 5);
	cout << s+1 << "\n";
	int pos = -1;
	rep(i, 1, n) {
		if(i == 1) pos = 1;
		else pos = max<int>(pos, mtrnd() % (i-1) + 1);
		cout << s[pos];
	}
	cout << "\n";
	
	return 0;
}
