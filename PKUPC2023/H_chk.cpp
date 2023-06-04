#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)
#define fi first
#define se second
#define mp make_pair
#define pb push_back

const int N = 1e6 + 5;

int n;
int a[N];
set<int> s1, s2, s3;

int main(int argc, char** argv) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	assert(argc == 3);
	ifstream inf(argv[1]);
	ifstream ouf(argv[2]);

	inf >> n;
	ouf >> a[1];
	if(a[1] == -1) {
		cerr << "ok -1" << "\n";
		return 0;
	}
	rep(i, 2, n) ouf >> a[i], assert(a[i] != 0);
	rep(i, 1, n) {
		if(s1.count(a[i])) {
			cerr << i << " " << a[i] << " [1]\n";
			return 1;
		}
		s1.emplace(a[i]);
		if(s2.count(i+a[i]) || s2.count(i+a[i]-n)) {
			cerr << i << " " << a[i] << " [2]\n";
			return 1;
		}
		s2.emplace(i+a[i]);
		if(s3.count(i-a[i]) || s3.count(i-a[i]+n)) {
			cerr << i << " " << a[i] << " [3]\n";
			return 1;
		}
		s3.emplace(i-a[i]);
	}
	cerr << "ok " << n << "\n";

	return 0;
}
