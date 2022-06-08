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

	int t = 1e6;
	rep(i, 1, t) {
		cerr << "#" << i << "...";
		system("./gen.exe > in");
		system("./arcane.exe < in > out");
		system("./arcane.exe < in > ans");
		if(system("diff -Z out ans")) return 1;
		cerr << "ok" << "\n";
	}
	
	return 0;
}