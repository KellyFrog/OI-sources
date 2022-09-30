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

int n, q;
char s[N];
map<string, int> v;
vector<pair<string, int>> vv;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> (s + 1);
    n = strlen(s + 1);

    rep(i, 1, n) {
	string ss = "";
	rep(j, i, n) {
	    ss += s[j];
	    if(!v.count(ss)) v[ss] = i;
	}
    }

    for(auto& e : v) vv.pb(e);
    cin >> q;
    while(q--) {
	ll k;
	cin >> k;
	if(k > vv.size()) {
	    cout << 0 << " " << 0 << "\n";
	    continue;
	}
	int s = vv[k-1].se;
	int t = s + vv[k-1].fi.length() - 1;
	cout << s << " " << t << "\n";
    }

    return 0;
}
