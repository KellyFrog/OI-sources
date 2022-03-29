#include <bits/stdc++.h>

#define rep(i, p, q) for (int i = int(p); i <= int(q); i++)
#define per(i, p, q) for (int i = int(p); i >= int(q); i--)

using namespace std;

typedef long long ll;

template <int T>
struct fast_io {
	char p[T], q[T], *p1, *p2, *q1, *q2;
	fast_io() {
		p1 = p2 = p;
		q1 = q, q2 = q + T;
	}
	inline char gc() {
		return p1 == p2 && (p2 = (p1 = p) + fread(p, 1, T, stdin)), p1 == p2 ? EOF : *p1++;
	}
	inline void pc(char c) {
		if (q1 == q2) q2 = (q1 = q) + fwrite(q, 1, T, stdout);
		*q1++ = c;
	}
	~fast_io() {
		fwrite(q, 1, q1 - q, stdout);
	}
};
fast_io<1<<20> io;

template <typename T = int32_t>
T read() {
	T res = 0;
	char ch;
	do ch = io.gc(); while (ch < 48 || ch > 57);
	do res = res * 10 + (ch & 15), ch = io.gc(); while (ch >= 48 && ch <= 57);
	return res;
}

template <typename T>
void _put(T x) {
	if (x >= 10) _put(x / 10);
	io.pc(48 ^ (x % 10));
}

template <typename T>
void put(T x, char ch = ' ') {
	_put(x);
	io.pc(ch);
}

int main() {
	// use freopen
	return 0;
}
