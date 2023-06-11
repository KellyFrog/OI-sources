#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)
#define fi first
#define se second
#define pb push_back
#define mp make_pair

const int L = 1 << 20;
char buf[L];
char *ps=buf, *pt=buf;

inline char getc() {
    if(ps == pt) {
	ps = buf;
	pt = buf + fread(buf, 1, L, stdin);
	if(ps == pt) return EOF;
    }
    return *ps++;
}

inline void read(int& x) {
    x = 0;
    char ch = ' ';
    while(!isdigit(ch)) ch = getchar();
    while(isdigit(ch)) x = 10 * x + (ch - '0'), ch = getchar();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
    return 0;
}
