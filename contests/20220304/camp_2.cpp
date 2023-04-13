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

std::mt19937_64 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

const int N = 1e3 + 5;
const int K = 5e6 + 5;

long double p[N][N];
long double prep[N], preval[N];
int n, k;

struct M {
	long double a[3][3];
	void clear() { memset(a, 0, sizeof a); }
	void unit() { clear(), a[1][1] = a[2][2] = 1; }
	M() {}
	M(long double x, long double y, long double z, long double w) {
		a[1][1] = x, a[1][2] = y;
		a[2][1] = z, a[2][2] = w;
	}
};

M operator * (const M& x, const M& y) {
	return M(
	x.a[1][1] * y.a[1][1] + x.a[1][2] * y.a[2][1],
	x.a[1][1] * y.a[1][2] + x.a[1][2] * y.a[2][2],
	x.a[2][1] * y.a[1][1] + x.a[2][2] * y.a[2][1],
	x.a[2][1] * y.a[1][2] + x.a[2][2] * y.a[2][2]
	);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	
	cin >> n >> k;
	--n;
	p[0][0] = 1;
	rep(i, 1, n) rep(j, 0, i) {
		if(j) p[i][j] = (p[i-1][j-1] + p[i-1][j]) / 2;
		else p[i][j] = p[i-1][j] / 2;
	}
	
	prep[0] = p[n][0];
	rep(i, 1, n) prep[i] = prep[i-1] + p[n][i];
	
	preval[0] = 0;
	rep(i, 1, n) preval[i] = p[n][i] * i + preval[i-1];
	
	long double f = (long double)n / 2;
	
	int pos = int(ceil(f));
	int pk = 1;
	while(pos <= n && pk < k) {
		M m(prep[pos-1], preval[n] - preval[pos-1], 0, 1), vec(f, 0, 1, 0), cur;
		cur.unit();
		vector<M> base(21);
		base[0] = m;
		for(int i = 1; i < 21; ++i) base[i] = base[i-1] * base[i-1];
		int pp = pk;
		cerr << pos << " " << pk << "\n";
		
		auto print = [&](const M& x) {
			rep(i, 1, 2) rep(j, 1, 2) cerr << x.a[i][j] << " \n"[j == 2];
		};
		
		per(i, 0, 20) {
			int ppp = pp + (1 << i);
			if(ppp <= pk) {
				M nxt = cur * base[i];
				cerr << "ppp = " << ppp << "\n";
				print(nxt);
				if((nxt * vec).a[1][1] < pos) {
					pp = ppp;
					cur = nxt;
				}
			}
		}
		pk = pp;
		f = (cur * m * vec).a[1][1];
		
		cerr << "f[" << pk << "] = " << f << "\n";
		
	}
	
	cout << f+1 << "\n";
	
	return 0;
}
