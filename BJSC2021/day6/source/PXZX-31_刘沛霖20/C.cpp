#include<bits/stdc++.h>
using namespace std;

template<typename T> void read(T &x) {
	x = 0; int f = 1;
	char c = getchar();
	for(; !isdigit(c); c = getchar())if(c == '-')f = -1;
	for(;  isdigit(c); c = getchar())x = x * 10 + c - '0';
	x = x * f;
}

long long A, B, X, Y;
long long ans = 0;
double k;
int f, u, r, l, d, b;
int tf, tu, tr, tl, td, tb;

int main() {
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
	read(A), read(B);
	read(b), read(u), read(r), read(l), read(d), read(f);
	k = (1.0 * B / A);
	X = 0, Y = 0;
	ans += d;
	A --, B --;
	while(true) {
		if(k * (double)(X + 1) >= Y && k * (double)(X + 1) <= Y + 1) {
			X ++;
			tu = u, tr = r, td = d, tl = l;
			u = tl, r = tu, d = tr, l = td;
			ans += d;
		}
		else {
			Y ++;
			tu = u, tf = f, td = d, tb = b;
			u = tb, f = tu, d = tf, b = td;
			ans += d;
		}
		if(X == A && Y == B)
			break;
	}
	printf("%lld\n", ans);
	
	return 0;
}
