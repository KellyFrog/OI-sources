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

const int N = 3e5 + 5;
const int M = 505;

map<string, int> scnt, rcnt;
string s[N], r[N], ss;
int n, m, a, b;

string rev(const string& s) {
    string res = s;
    for(char& c : res) {
	c = 'Y' + 'N' - c;
    }
    return res;
}

inline void dfs(int p) {
    if(p == m) {
	if(!scnt.count(ss) && !rcnt.count(ss)) {
	    cout << ss << endl;
	    exit(0);
	}
    } else {
	ss[p] = 'N';
	dfs(p+1);
	ss[p] = 'Y';
	dfs(p+1);
    }
}

string pol[N<<1]; int ps;

int main() {
    freopen("answer.in", "r", stdin);
    freopen("answer.out", "w", stdout);
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> n >> m >> a >> b;

    rep(i, 1, n) {
	cin >> s[i];
	r[i] = rev(s[i]);
	++scnt[s[i]];
	++rcnt[r[i]];
	pol[++ps] = r[i];
	pol[++ps] = s[i];
    }

    if(a == 0 && b == 0) {
        ss.resize(m);
	dfs(0);
	cout << -1 << endl;
	return 0;
    }

    sort(pol+1, pol+ps+1);

    rep(i, 1, ps) {
	if(pol[i] == pol[i-1]) continue;
	if(scnt[pol[i]] == a && scnt[rev(pol[i])] == b) {
	    cout << pol[i] << endl;
	    return 0;
	}
    }
    cout << -1 << endl;
    
    return 0;
}
    
