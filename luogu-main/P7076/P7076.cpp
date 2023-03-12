#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <stack>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef pair<int, int> pii;
#define rg register
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pf push_front
#define rep(i, s, t) for(rg int (i) = s; (i) <= t; i++) 
#define per(i, s, t) for(rg int (i) = t; (i) >= s; i--)

template<typename T>
void qread(T& x) {
  x = 0;
  rg char ch = ' '; rg int ps = 1;
  while(!isdigit(ch) && ch != '-') ch = getchar();
  if(ch == '-') ps = -1, ch = getchar();
  while(isdigit(ch)) x = 10 * x + ch - '0', ch = getchar();
  x *= ps;
}

template<typename T>
void qwrite(T x) {
  if(x < 0) putchar('-'), x = -x;
  if(x < 10) return putchar('0' + x), void();
  qwrite(x / 10), putchar('0' + (x % 10));
}

template<typename T>
void qwrite(T x, char ch) {
  qwrite(x), putchar(ch);
}

int n, m, k, q;
ull base = 0;

bool bad[70];

int main() {
  qread(n), qread(m), qread(k), qread(q);
  rep(i, 1, n) {
    ull x; qread(x);
    base |= x;
  }
  rep(i, 1, m) {
    int x, y; qread(x), qread(y);
    if((base & ((ull)1 << x)) == 0 && bad[x] == 0) bad[x] = 1, q--;
  }
  //cerr << k << " " << q << "\n";
  if(q==64&&!n)puts("18446744073709551616");
  else qwrite(((ull)1 << q) - n, '\n');
  return 0;
}