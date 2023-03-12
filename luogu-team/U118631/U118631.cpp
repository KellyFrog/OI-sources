#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)
#define fi first
#define se second
#define pb push_back
#define mp make_pair

const int N = 5e5 + 5;

set<pair<int, int>> s;
int n, m, d;
int a[N], last[N], st[21][N];

int main() {
    // freopen("subsequence.in", "r", stdin);
    // freopen("subsequence.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> n >> m >> d;
    rep(i, 1, n) cin >> a[i];
    int p = n;
    while(p && s.size() < d) {
		s.erase(mp(last[a[p]], a[p]));
	    s.insert(mp(last[a[p]] = p, a[p]));
		--p;
    }
    if(p) ++p;
    st[0][p] = n;
    rep(i, p+1, n) st[0][i] = n+1;
    per(i, 1, p) {
		s.erase(mp(last[a[i]], a[i]));
		s.insert(mp(last[a[i]] = i, a[i]));
		st[0][i] = s.rbegin()->fi;
    }
    rep(j, 1, 20) rep(i, 1, n) {
		st[j][i] = st[j-1][i] >= n ? n+1 : st[j-1][st[j-1][i]+1];
    }
    while(m--) {
		int l, r;
		cin >> l >> r;
		int p = l;
		int ans = 0;
		per(i, 0, 20) {
		    if(st[i][p] <= r) p = st[i][p]+1, ans |= 1 << i;
		    if(p >= n) break;
		}
		cout << ans + 1 << "\n";
    }
    cout.flush();
    
    return 0;
}