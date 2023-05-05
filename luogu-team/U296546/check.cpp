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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	rep(i, 1, 10000000) {
		cerr << i << "\n";
		system("./gen.exe > in");
		system("./std.exe < in > ans");
		system("./sol.exe < in > out");
		if(system("./checker.exe in out ans")) {
			return 1;
		}
	}
	
	return 0;
}
