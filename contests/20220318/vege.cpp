#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)
#define fi first
#define se second
#define pb push_back
#define mp make_pair

const int N = 2e3 + 5;

int n, k;
vector<int> adj[N];
int pre[N], pos[N];
int w[N];

struct Q {
    bitset<N> p;
    int cnt;
    ll ans;
    Q() : cnt(0), ans(0), p() {}
    Q(int cnt, ll ans, const bitset<N>& p) : cnt(cnt), ans(ans), p(p) {}
};

bool operator < (const Q& x, const Q& y) {
    if(x.cnt != y.cnt) return x.cnt < y.cnt;
    if(x.ans != y.ans) return x.ans > y.ans;
    rep(i, 1, n) if(x.p[i] != y.p[i]) return x.p[i] < y.p[i];
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    freopen("vege.in", "r", stdin);
    freopen("vege.out", "w", stdout);

    cin >> n >> k;
    rep(i, 1, n) {
	int w, d;
	cin >> w >> d;
	adj[d].pb(w);
    }

    rep(i, 1, n) sort(adj[i].begin(), adj[i].end());
    rep(i, 1, n) {
	pre[i] = pre[i-1] + adj[i].size();
	for(int j = 0; j < adj[i].size(); ++j) {
	    pos[pre[i-1]+j+1] = i;
	    w[pre[i-1]+j+1] = adj[i][j];
	}
    }

    priority_queue<pair<int, int>> pq;
    Q ans0;
    per(i, 1, n) {
	for(int j = 0; j < adj[i].size(); ++j) {
	    pq.push(mp(-adj[i][j], pre[i-1]+j+1));
	}
	if(!pq.empty()) {
	    ++ans0.cnt;
	    ans0.ans += -pq.top().fi;
	    ans0.p[pq.top().se] = 1;
	    pq.pop();
	}
    }
    set<Q> s;
    s.insert(ans0);
    while(k--) {
	assert(!s.empty());
	Q cur = *s.rbegin();
	s.erase(--s.end());
	cout << cur.cnt << " " << cur.ans << "\n";
	rep(i, 1, n) {
	    if(cur.p[i]) {
		Q o = cur;
		--o.cnt;
		o.ans -= w[i];
		o.p[i] = 0;
		s.insert(o);
	    }
	}
	set<pair<int, int>> ss;
	rep(i, 1, n) {
	    if(cur.p[i]) {
		ss.insert(mp(w[i], i));
	    } else if(!ss.empty()) {
		auto it = ss.lower_bound(mp(w[i], (int)1e9));
		if(it != ss.begin()) {
		    --it;
		    Q o = cur;
		    o.p[it->se] = 0; o.ans -= w[it->se];
		    o.p[i] = 1; o.ans += w[i];
		    s.insert(o);
		}
	    }
	}
	while(s.size() > k) {
	    s.erase(s.begin());
	}
    }

    cout.flush();

    return 0;
}
