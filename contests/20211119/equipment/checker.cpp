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

int n, m, k;
int c[N], a[N], b[N];
int a1[N], a2[N], b1[N], b2[N];
bool vis[N];

int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    assert(argc == 4);
    
    ifstream inf(argv[1]);
    ifstream ouf(argv[2]);
    ifstream anf(argv[3]);

    inf >> n >> m >> k;
    rep(i, 1, n) inf >> c[i];
    rep(i, 1, m) inf >> a[i] >> b[i];
    rep(i, 1, n) a1[i] = a2[i] = a[i], b1[i] = b2[i] = b[i];

    int jk; anf >> jk;
    rep(i, 1, n) vis[i] = 0;
    rep(i, 1, m) vis[a1[i]] = 1;
    rep(i, 1, jk) {
	int p; anf >> p;
	if(vis[b1[p]]) {
	    cerr << "Jury WA!" << "\n";
	    return 1;
	}
	vis[a1[p]] = 0;
	vis[b1[p]] = 1;
	swap(a1[p], b1[p]);
    }

    int pk; ouf >> pk;
    assert(pk <= k);
    rep(i, 1, n) vis[i] = 0;
    rep(i, 1, m) vis[a2[i]] = 1;
    rep(i, 1, pk) {
	int p; ouf >> p;
	if(vis[b2[p]]) {
	    cerr << "WA, invaild move on pos = " << p << " in " << i << "-th move" << " b2 = " << b2[p] << "\n";
	    return 1;
	}
	vis[a2[p]] = 0;
	vis[b2[p]] = 1;
	swap(a2[p], b2[p]);
    }

    per(i, 1, m) {
	if(c[a1[i]] != c[a2[i]]) {
	    cerr << "WA, pans != jans, on pos " << i << " read jans = " << c[a1[i]] << " get pans = " << c[a2[i]] << "\n";
	    return 1;
	}
    }

    cerr << "OK! n = " << n << ", m = " << m << ", k = " << k << "\n";
    
    return 0;
}
    
