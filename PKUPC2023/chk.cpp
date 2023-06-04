#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)
#define fi first
#define se second
#define mp make_pair
#define pb push_back

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	rep(i, 2, 1e6) {
		cerr << "#" << i << "...";
		system("./gen.exe > C.in");
		system("./C.exe < C.in > C.out");
		if(system("./C_chk.exe C.in C.out")) return 1;
	}

	return 0;
}
