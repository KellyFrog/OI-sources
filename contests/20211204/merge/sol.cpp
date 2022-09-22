/*
 * Author: chenkaifeng @BDFZ
 */
 
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

std::mt19937 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

const int N = 1e5 + 5;

int n, m;
int a[N], b[N];

bool check(int x) {
//    cerr << "check = " << x << "\n";
    priority_queue<int> pq;
    int p = n;
    int cnt = 0, t = 0;

    rep(i, 1, m) {
	int val = x - b[i];
	pq.push(val);
	++cnt;
    }
    
    while(cnt < 2*n && p) {
	int mx = pq.top(); pq.pop();
	int smx = pq.top();
	++t;

//	cerr << "mx = " << mx << " " << smx << " p = " << p << " " << a[p] << " siz = " << pq.size() << "\n";
	
	if(a[p] > mx) {
	    return 0;
	}
	
	bool ok = 1;

	if(pq.empty()) {

	} else {
	
	    if(max(smx, mx-b[1]) < a[p]) {
		ok = 0;
	    } else {
		int val = mx - b[1];
		if(val < smx) {
		    int pp = upper_bound(a+1, a+n+1, val)-a;
		    int cnt = p-pp+1;
		    if(cnt > 1) ok = 0;
		} else {
		    ok = 1;
		}
	    }
	}

//	cerr << "ok = " << ok << "\n";

//	cerr << pq.size() << " top = " << pq.top() << "\n";
	
	if(ok) {
	    cnt += m-1;
	    rep(i, 1, m) {
		int x = mx - b[i];
		pq.push(x);
	    }
	} else {
	    --p;
	}

//	cerr << "top = " << pq.top() << "\n";
    }
    // cerr << "ok" << "\n";
    return 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> n >> m;
    rep(i, 1, n) cin >> a[i];
    rep(i, 1, m) cin >> b[i];

    sort(a + 1, a + n + 1);
    sort(b + 1, b + m + 1);

    if(n == m) {
	int ans = 0;
	rep(i, 1, n) ans = max(ans, a[i] + b[n-i+1]);
	cout << ans << "\n";
	return 0;
    }

    int l = a[n] + b[1], r = 1e9;
    int res = -1;
    
    while(l <= r) {
	int mid = l + r >> 1;
	if(check(mid)) {
	    res = mid;
	    r = mid - 1;
	} else {
	    l = mid + 1;
	}
    }
    
    cout << res << "\n";
    return 0;
}
    
