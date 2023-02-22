#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;

typedef long long ll;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pf push_front
#define rep(i, s, t) for (int i = s; i <= t; ++i)
#define per(i, s, t) for (int i = t; i >= s; --i)

const int N = 305;

int n, m, k;
deque<int> dq[N];

int main(int argc, char** argv) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	registerTestlibCmd(argc, argv);
	int t = inf.readInt();
	rep(T, 1, t) {
		int n = inf.readInt(), m = inf.readInt(), k = inf.readInt();
		int l = ouf.readInt(m, 2*m), cnt = 0;
		rep(i, 1, l) {
			int op = ouf.readInt();
			if(op == 1) {
				int p = ouf.readInt();
				int x = inf.readInt();
				if(!dq[p].empty() && dq[p].back() == x) dq[p].pop_back();
				else dq[p].push_back(x);
				++cnt;
			} else {
				int x = ouf.readInt(), y = ouf.readInt();
				if(x == y) quitf(_wa, "T = %d, i = %d, x = y\n", T, i);
				if(dq[x].empty() || dq[y].empty()) quitf(_wa, "T = %d, i = %d: dq is empty: %d %d", T, i, dq[x].size(), dq[y].size());
				if(dq[x].front() != dq[y].front()) quitf(_wa, "T = %d, i = %d: dq[x].front() != dq[y].front()", T, i);
				dq[x].pop_front(), dq[y].pop_front();
			}
		}
		rep(i, 1, n) if(!dq[i].empty()) quitf(_wa, "T = %d, dq[%d] not empty", T, i);
		if(cnt != m) quitf(_wa, "T = %d, didn't read all a[i]", T);
	}
	quitf(_ok, "ok T = %d", t);
	
	return 0;
}
