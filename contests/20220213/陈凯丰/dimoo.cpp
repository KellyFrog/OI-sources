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

namespace nqio{const unsigned R=4e5,W=4e5;char*a,*b,i[R],o[W],*c=o,*d=o+W,h[40],*p=h,y;bool s;struct q{void r(char&x){x=a==b&&(b=(a=i)+fread(i,1,R,stdin),a==b)?-1:*a++;}void f(){fwrite(o,1,c-o,stdout);c=o;}~q(){f();}void w(char x){*c=x;if(++c==d)f();}q&operator>>(char&x){do r(x);while(x<=32);return*this;}q&operator>>(char*x){do r(*x);while(*x<=32);while(*x>32)r(*++x);*x=0;return*this;}template<typename t>q&operator>>(t&x){for(r(y),s=0;!isdigit(y);r(y))s|=y==45;if(s)for(x=0;isdigit(y);r(y))x=x*10-(y^48);else for(x=0;isdigit(y);r(y))x=x*10+(y^48);return*this;}q&operator<<(char x){w(x);return*this;}q&operator<<(char*x){while(*x)w(*x++);return*this;}q&operator<<(const char*x){while(*x)w(*x++);return*this;}template<typename t>q&operator<<(t x){if(!x)w(48);else if(x<0)for(w(45);x;x/=10)*p++=48|-(x%10);else for(;x;x/=10)*p++=48|x%10;while(p!=h)w(*--p);return*this;}}qio;}using nqio::qio;

const int N = 1e7 + 5;
const unsigned long long P = 12345678901;

int n, k;
int a[N], b[N];
ll sum = 0;

void solve1() {
	bool ok = 1;
	rep(i, 1, n) if(a[i] > 1) ok = 0;
	int kk = 0;
	if(!ok) kk = min(k, 2 * n);
	// int kk = k;
	rep(t, 1, kk) {
		rep(i, 1, n) b[i] = a[i];
		rep(i, 1, n) {
			if(a[i]) {
				--b[i];
				++b[i%n+1];
			}
		}
		rep(i, 1, n) a[i] = b[i];
	}
	if(sum < n) {
		rep(i, 1, n) assert(0 <= a[i] && a[i] <= 1);
		int k0 = k - kk;
		rep(i, 1, n) {
			int ii = (i + k0 - 1) % n + 1;
			b[ii] = a[i];
		}
		rep(i, 1, n) a[i] = b[i];
		
	}
	
	unsigned long long ans = 0;
	unsigned long long base = 1;
	rep(i, 1, n) {
		base *= P;
		ans += base * (a[i] + 1);
	}
	cout << ans << "\n";
}

void solve2() {
	
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

    freopen("dimoo.in", "r", stdin);
    freopen("dimoo.out", "w", stdout);
	
	qio >> n >> k;
	rep(i, 1, n) qio >> a[i];
	
	rep(i, 1, n) sum += a[i];
	
	solve1();
	
	return 0;
}
