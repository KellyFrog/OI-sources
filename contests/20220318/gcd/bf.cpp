#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)
#define fi first
#define se second
#define pb push_back
#define mp make_pair

const int N = 1e5 + 5;

bool vis[N];
int n, q;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> n >> q;
    rep(i, 1, q) {
	char op;
	cin >> op;
	if(op == 'S') {
	    int x; cin >> x;
	    vis[x] ^= 1;
	} else {
	    int l, r;
	    cin >> l >> r;
	    bool ok = 0;
	    rep(i, l, r) {
		rep(j, i+1, r) {
		    if(vis[i] && vis[j] && __gcd(i, j) > 1) ok = 1;
		}
		if(ok) break;
	    }
	    cout << (ok ? "yes" : "no") << "\n";
	}
    }
    
    return 0;
}
