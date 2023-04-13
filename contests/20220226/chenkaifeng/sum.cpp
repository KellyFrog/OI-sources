#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)
#define fi first
#define se second
#define pb push_back
#define mp make_pair

const int N = 1e6 + 5;
const int base = 131;
const int mod = 1234567891;

int ans[N];
string s[N];
vector<int> hash[N];
int pw[N];
bool ok[N];
int n;

bool compare(int i, int j) { //return i > j
    rep(k, 0, max((int)s[i].length(), (int)s[j].length())-1) {
	char si = k < s[i].length() ? s[i][k] : '0';
	char sj = k < s[j].length() ? s[j][k] : '0';
	if(si != sj) return si > sj;
    }
    return 0;
}

int fuckpos;

bool check(int p) {
    if(p == -1) return 1;
    int cnt = 0;
    rep(i, 1, n) {
	if(!ok[i] && s[i].length() > p && s[i][p] == '1') {
	    ++cnt;
	}
    }
    if(cnt > 1) return 0;
    if(cnt == 1) {
	int pos = -1;
	rep(i, 1, n) if(!ok[i] && s[i].length() > p && s[i][p] == '1') {
	    s[i][p] = '0';
	    pos = i;
	}
	bool ret = check(p-1);
	s[pos][p] = '1';
	return ret;
    } else {
	int mx = -1;
	rep(i, 1, n) if(!ok[i]) mx = i;
	rep(i, 1, n) if(!ok[i]) {
	    if(compare(mx, i)) mx = i;
	}
	ok[mx] = 1;
	bool ret = check(p-1);
	ok[mx] = 0;
	return ret;
    }
}

int main() {
    freopen("sum.in", "r", stdin);
    freopen("sum.out", "w", stdout);
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
    cin >> n;
    rep(i, 1, n) cin >> s[i];
    rep(i, 1, n) {
	reverse(s[i].begin(), s[i].end());
    }

    per(i, 0, 201) {
	int cnt = 0;
	rep(j, 1, n) if(!ok[j] && s[j].length() > i && s[j][i] == '1') {
	    s[j][i] = '0';
	    ++cnt;
	}
	if(cnt == 0 && check(i-1)) ans[i] = 0;
	else {
	    ans[i] = 1;
	    assert(cnt <= 1);
	    if(!cnt) {
		int mx = -1;
		rep(j, 1, n) if(!ok[j]) mx = j;
		rep(j, 1, n) if(!ok[j]) {
		    if(compare(mx, j)) mx = j;
		}
		ok[mx] = 1;
		
	    }
	}
    }

    int pos = 202;
    while(pos >= 0 && ans[pos] == 0) --pos;
    per(i, 0, pos) cout << ans[i]; cout << endl;
    
    return 0;
}
