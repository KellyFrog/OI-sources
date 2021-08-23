#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define fi first
#define se second
#define rg register
#define pb push_back
#define mp make_pair
#define rep(i, s, t) for(rg int i = (s); i <= (t); i++)
#define per(i, s, t) for(rg int i = (t); i >= (s); i--)

const int N = 2e5 + 5;

char S[N];
int n, cnt[N];
int st[21][N], sast[21][N], lg2[N];
int sa[N], rk[N], h[N];
pair<pair<int, int>, int> cur[N], tmp[N];

int rt[N], lson[N << 5], rson[N << 5], sum[N << 5], nodecnt;

inline void add(int& cur, int old, int p, int x, int l, int r) {
  cur = ++nodecnt;
  lson[cur] = lson[old];
  rson[cur] = rson[old];
  sum[cur] = sum[old] + x;
  if(l == r) return ;
  int mid = l + r >> 1;
  if(p <= mid) add(lson[cur], lson[old], p, x, l, mid);
  else add(rson[cur], rson[old], p, x, mid + 1, r); 
}

inline int querysum(int cur, int ql, int qr, int l, int r) {
  if(ql <= l && r <= qr) return sum[cur];
  if(!cur) return 0;
  int mid = l + r >> 1;
  int res = 0;
  if(ql <= mid) res += querysum(lson[cur], ql, qr, l, mid);
  if(mid < qr) res += querysum(rson[cur], ql, qr, mid + 1, r);
  return res;
}

inline void rsort() {
  static int pre[N];
  static const int m = 5e3;
  memset(pre, 0, sizeof pre);
  rep(i, 1, n) pre[cur[i].fi.se]++;
  rep(i, 1, m) pre[i] += pre[i-1];
  per(i, 1, n) tmp[pre[cur[i].fi.se]--] = cur[i];
  


  memset(pre, 0, sizeof pre);
  rep(i, 1, n) pre[cur[i].fi.fi]++;
  rep(i, 1, m) pre[i] += pre[i-1];
  per(i, 1, n) cur[pre[tmp[i].fi.fi]--] = tmp[i];

  int p = 1;
  rk[cur[1].se] = 1;
  rep(i, 2, n) {
    if(cur[i].fi != cur[i-1].fi) p++;
    rk[cur[i].se] = p;
  }
}

inline void SA() {
  rep(i, 1, n) rk[i] = S[i];
  for(int len = 1; len / 2 <= n; len <<= 1) {
    rep(i, 1, n) cur[i] = mp(mp(rk[i], i+len > n ? 0 : rk[i+len]), i);
    rsort();
  }
  rep(i, 1, n) sa[rk[i]] = i;
}

inline void buildheight() {
  int p = 0;
  rep(i, 1, n) {
    if(p) p--;
    while(i+p <= n && sa[rk[i]-1]+p <= n && S[i+p] == S[sa[rk[i]-1]+p]) p++;
    h[rk[i]] = p;
  }
}

inline void buildST() {
  lg2[0] = -1;
  rep(i, 1, n) lg2[i] = lg2[i>>1] + 1;
  rep(i, 1, n) st[0][i] = h[i], sast[0][i] = sa[i];
  rep(j, 1, 19) rep(i, 1, n) {
    if(i + (1 << j) - 1 > n) continue;
    sast[j][i] = max(sast[j-1][i], sast[j-1][i+(1<<j-1)]);
    st[j][i] = min(st[j-1][i], st[j-1][i+(1<<j-1)]);
  }
}

inline int query(int L, int R) {
  if(L > R) return 0;
  return min(st[lg2[R-L+1]][L], st[lg2[R-L+1]][R-(1<<lg2[R-L+1])+1]);
}

inline int querysa(int L, int R) {
  return max(sast[lg2[R-L+1]][L], sast[lg2[R-L+1]][R-(1<<lg2[R-L+1])+1]);
}

inline int lcp(int x, int y) {
  if(x == y) return n + 1;
  x = rk[x], y = rk[y];
  if(x > y) swap(x, y);
  return query(x + 1, y);
}

inline void getrange(int s, int t, int& resL, int& resR) {
  int p = rk[s];
  resL = resR = p;
  {
    int L = 1, R = p-1;
    while(L <= R) {
      int mid = L + R >> 1;
      if(lcp(sa[mid], s) >= t - s + 1) resL = mid, R = mid-1;
      else L = mid+1;
    }
  }
  {
    int L = p+1, R = n;
    while(L <= R) {
      int mid = L + R >> 1;
      if(lcp(sa[mid], s) >= t - s + 1) resR = mid, L = mid+1;
      else R = mid-1;
    }
  }
}

int main() {
  freopen("B.in", "r", stdin);
  freopen("B.out", "w", stdout);
  cin >> n >> S + 1;
  SA();
  buildheight();
  buildST();
  rep(i, 1, n) {
    add(rt[i], rt[i-1], rk[i], 1, 1, n);
  }
  ll ans = 0;
  rep(i, 1, n) {
    rep(j, h[rk[i]]+1, n) {
      if(i >= j) continue;
      int L = -1, R = -1;
      getrange(i, j, L, R);
      int p2 = R - L + 1;
      int lim = n - (j - i + 1) + 1;
      rep(k, i, j-1) {
	int LL = -1, RR = -1;
	getrange(i, k, LL, RR);
	int p1 = querysum(rt[lim], LL, RR, 1, n);
	if(p1 == p2) ans++;
	
      }
    }
  }
  cout << ans << "\n";
  fclose(stdin);
  fclose(stdout);
  return 0;
}
