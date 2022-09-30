#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)
#define fi first
#define se second
#define pb push_back
#define mp make_pair

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int T = 1e7;
    rep(i, 1, T) {
	cerr << "test #" << i << "... ";
	system("./gen.exe > perm.in");
	system("./bf.exe < perm.in > perm.ans");
	system("./perm.exe < perm.in > perm.out");
	if(system("diff -Z perm.out perm.ans")) {
	    cerr << "wa!" << "\n";
	    return 1;
	}
	cerr << "ok!" << "\n";
    }

    return 0;
}
