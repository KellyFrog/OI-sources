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

    int T = 1e6;
    rep(i, 1, T) {
	cerr << "test #" << i << "... ";
	system("./gen.exe > scc.in");
	system("./bf.exe < scc.in > scc.ans");
	system("./scc.exe");
	if(system("diff -Z scc.out scc.ans")) {
	    cerr << "WA!" << "\n";
	    return 1;
	}
	cerr << "OK!" << "\n";
    }

    return 0;
}
