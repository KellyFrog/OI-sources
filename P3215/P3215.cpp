#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define fi first
#define se second

#if __cplusplus < 201703L
#define rg register
#else
#define rg
#endif

#define mp make_pair
#define pb push_back
#define pf push_front

#define rep(i, s, t) for (rg int i = s; i <= t; i++)
#define per(i, s, t) for (rg int i = t; i >= s; i--)

template <typename T>
inline void chkmax(T& x, T y) {
  x = x < y ? y : x;
}
template <typename T>
inline void chkmax(T& x, T y, T z) {
  x = y > z ? y : z;
}
template <typename T>
inline void chkmin(T& x, T y) {
  x = x < y ? x : y;
}
template <typename T>
inline void chkmin(T& x, T y, T z) {
  x = y < z ? y : z;
}

const int N = 2e5 + 5;
const int inf = 0x3f3f3f3f;

struct SplayNode {
  int fa, siz, num, sum, val[4], son[2];
  int inv, rev, modi;
};

SplayNode tree[N];
int n, q;
char S[N];
int tot = 1;

#define sroot 1
#define root lson(sroot)

#define son(x, p) tree[x].son[p]
#define lson(x) son(x, 0)
#define rson(x) son(x, 1)
#define fa(x) tree[x].fa
#define siz(x) tree[x].siz
#define val(x, p) tree[x].val[p]
#define lmin(x) val(x, 0)
#define lmax(x) val(x, 1)
#define rmin(x) val(x, 2)
#define rmax(x) val(x, 3)
#define num(x) tree[x].num
#define sum(x) tree[x].sum
#define rev(x) tree[x].rev
#define inv(x) tree[x].inv
#define modi(x) tree[x].modi
#define pos(x) (rson(fa(x)) == x)

inline void pushup(int cur) {
  lmax(cur) = lmin(cur) = rmax(cur) = rmin(cur) = 0;

  chkmax(lmax(cur), lmax(lson(cur)));
  chkmax(lmax(cur), sum(lson(cur)) + num(cur));
  chkmax(lmax(cur), sum(lson(cur)) + num(cur) + lmax(rson(cur)));

  chkmax(rmax(cur), rmax(rson(cur)));
  chkmax(rmax(cur), sum(rson(cur)) + num(cur));
  chkmax(rmax(cur), sum(rson(cur)) + num(cur) + rmax(lson(cur)));

  chkmin(lmin(cur), lmin(lson(cur)));
  chkmin(lmin(cur), sum(lson(cur)) + num(cur));
  chkmin(lmin(cur), sum(lson(cur)) + num(cur) + lmin(rson(cur)));

  chkmin(rmin(cur), rmin(rson(cur)));
  chkmin(rmin(cur), sum(rson(cur)) + num(cur));
  chkmin(rmin(cur), sum(rson(cur)) + num(cur) + rmin(lson(cur)));

  siz(cur) = siz(lson(cur)) + siz(rson(cur)) + 1;
  sum(cur) = sum(lson(cur)) + sum(rson(cur)) + num(cur);
}

inline void setmodi(int cur, int x) {
  if (cur == 0 || x == 0) return;
  modi(cur) = num(cur) = x;
  inv(cur) = 0;
  if (x == 1) {
    sum(cur) = lmax(cur) = rmax(cur) = siz(cur);
    lmin(cur) = rmin(cur) = 0;
  } else {
    lmax(cur) = rmax(cur) = 0;
    sum(cur) = lmin(cur) = rmin(cur) = -siz(cur);
  }
}

inline void setinv(int cur) {
	if(cur == 0) return;
  inv(cur) ^= 1;
  lmin(cur) *= -1;
  lmax(cur) *= -1;
  rmin(cur) *= -1;
  rmax(cur) *= -1;
  num(cur) *= -1;
  sum(cur) *= -1;
  modi(cur) *= -1;
  swap(lmin(cur), lmax(cur));
  swap(rmin(cur), rmax(cur));
}

inline void setrev(int cur) {
	if(cur == 0) return;
  rev(cur) ^= 1;
  swap(lson(cur), rson(cur));
  swap(lmax(cur), rmax(cur));
  swap(lmin(cur), rmin(cur));
}

inline void pushdown(int cur) {
  if (inv(cur)) {
    setinv(lson(cur));
    setinv(rson(cur));
    inv(cur) = 0;
  }
  if (modi(cur)) {
    setmodi(lson(cur), modi(cur));
    setmodi(rson(cur), modi(cur));
    modi(cur) = 0;
  }
  if (rev(cur)) {
    setrev(lson(cur));
    setrev(rson(cur));
    rev(cur) = 0;
  }
}

inline void connect(int x, int fa, int p) {
  son(fa, p) = x;
  fa(x) = fa;
}

inline void rotate(int cur) {
  int fa = fa(cur);
  pushdown(fa);
  pushdown(cur);
  int pos = pos(cur);
  connect(cur, fa(fa), pos(fa));
  connect(son(cur, pos ^ 1), fa, pos);
  connect(fa, cur, pos ^ 1);
  pushup(fa);
  pushup(cur);
  pushup(fa(cur));
}

inline void splay(int from, int to) {
  to = fa(to);
  while (fa(from) != to) {
    int f = fa(from);
    if (fa(f) == to) {
      rotate(from);
    } else if (pos(from) == pos(f)) {
      rotate(f);
      rotate(from);
    } else {
      rotate(from);
      rotate(from);
    }
  }
}

inline int kth(int cur, int k) {
  pushdown(cur);
  if (k <= siz(lson(cur)))
    return kth(lson(cur), k);
  else if (k == siz(lson(cur)) + 1)
    return cur;
  else
    return kth(rson(cur), k - siz(lson(cur)) - 1);
}

inline void build(int& cur, int fa, int pos, int L, int R) {
  if (L > R) return;
  cur = ++tot;
  int mid = L + R >> 1;
  siz(cur) = 1;
  if(mid == 1 || mid == n+1) num(cur) = 0;
  else num(cur) = (S[mid - 1] == '(' ? 1 : -1);
  connect(cur, fa, pos);
  build(lson(cur), cur, 0, L, mid - 1);
  build(rson(cur), cur, 1, mid + 1, R);
  pushup(cur);
}

inline void build() { build(root, sroot, 0, 1, n + 2); }

int main() {
  scanf("%d%d%s", &n, &q, S + 1);
  build();
  // dfs(root); cerr << "\n";
  while (q--) {
    static char op1[10], op2[10];
    int L, R;
    scanf("%s%d%d", op1, &L, &R);
    L++, R++;
    int nd1 = kth(root, L - 1);
    int nd2 = kth(root, R + 1);
    splay(nd1, root);
    splay(nd2, rson(root));
    if (op1[0] == 'R') {
      scanf("%s", op2);
      setmodi(lson(nd2), op2[0] == '(' ? 1 : -1);
    } else if (op1[0] == 'Q') {
    	
      printf("%d\n", (abs(lmin(lson(nd2))) + 1) / 2 + (abs(rmax(lson(nd2))) + 1) / 2);
    } else if (op1[0] == 'S') {
      setrev(lson(nd2));
    } else if (op1[0] == 'I') {
      setinv(lson(nd2));
    }
    pushup(nd2);
    pushup(root);
  }
  return 0;
}