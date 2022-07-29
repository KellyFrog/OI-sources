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

const int N = 1e6 + 5;

int n, m, k;
int a[N], pa;
int b[N], pb;
set<pair<int, int>> s[N];
int r1[N], c1[N], r2[N], c2[N], mr[N], mc[N], qr[N], qc[N];
int bel[N], qbel[N], cbel[N];
int t[N], ans[N], tmp[N], tmp2[N];
vector<pair<int, int>> adj[N];

struct O {
  int t, l, r, x, op, pos;
} op[N*10];

int opp;

inline int lowbit(int x) { return x & (-x); }
inline void add(int x, int val) { for(int x0 = x; x0 <= max(pa, pb); x0 += lowbit(x0)) t[x0] += val; }
inline int query(int x) { int ret = 0; for(int x0 = x; x0; x0 -= lowbit(x0)) ret += t[x0]; return ret; }

int modi[N<<2], addi[N<<2], sum[N<<2];

inline void setmod(int o, int x, int l, int r) {
  modi[o] = x;
  addi[o] = 0;
  sum[o] = x * (r - l + 1);
}

inline void setadd(int o, int x, int l, int r) {
  if(modi[o] != -1) {
    setmod(o, modi[o] + x, l, r);
  } else {
    addi[o] += x;
    sum[o] += x * (r - l + 1);
  }
}

inline void pushdown(int o, int l, int r) {
  int mid = l + r >> 1;
  if(modi[o] != -1) {
    setmod(o << 1, modi[o], l, mid);
    setmod(o << 1 | 1, modi[o], mid + 1, r);
    modi[o] = -1;
  }
  if(addi[o]) {
    setadd(o << 1, addi[o], l, mid);
    setadd(o << 1 | 1, addi[o], mid + 1, r);
    addi[o] = 0;
  }
}

inline void pushup(int o) {
  sum[o] = sum[o << 1] + sum[o << 1 | 1];
}

inline void set0(int o, int ql, int qr, int l, int r) {
  if(ql > qr) return;
  if(ql <= l && r <= qr) return setmod(o, 0, l, r), void();
  pushdown(o, l, r);
  int mid = l + r >> 1;
  if(ql <= mid) set0(o << 1, ql, qr, l, mid);
  if(mid < qr) set0(o << 1 | 1, ql, qr, mid + 1, r);
  pushup(o);
}

inline void add(int o, int ql, int qr, int x, int l, int r) {
  if(ql > qr) return;
  if(ql <= l && r <= qr) return setadd(o, x, l, r), void();
  pushdown(o, l, r);
  int mid = l + r >> 1;
  if(ql <= mid) add(o << 1, ql, qr, x, l, mid);
  if(mid < qr) add(o << 1 | 1, ql, qr, x, mid + 1, r);
  pushup(o);
}

inline int query(int o, int p, int l, int r) {
  if(p > r) return 0;
  if(l == r) return sum[o];
  pushdown(o, l, r);
  int mid = l + r >> 1;
  if(p <= mid) return query(o << 1, p, l, mid);
  else return query(o << 1 | 1, p, mid + 1, r);
}

//t, l, r, x, op, pos;


void solve(int id) {
  setmod(1, 0, 0, 0);
  opp = 0;

  //cerr << "s=" << id << "\n";
  //cerr << "cover = " << r1[id] << " " << c1[id] << " " << r2[id] << " " << c2[id] << "\n";
  
  for(auto ee : adj[id]) {
    int tp = ee.fi, o = ee.se;
    if(tp == 1) {
      //cerr << "c@ " << r1[o] << " " << c1[o] << " " << r2[o] << " " << c2[o] << "\n";
      op[++opp] = {r2[o], c1[o], c2[o], 1, 1, o};
      op[++opp] = {r1[o]-1, c1[o], c2[o], -1, 2, o};
      op[++opp] = {r1[o], c1[o], c2[o], 0, 5, o};
    } else if(tp == 2) {
      //cerr << "q@ " << qr[o] << " " << qc[o] << "\n";
      op[++opp] = {qr[o], qc[o], 0, 0, 4, o};
    } else {
      //cerr << "m@ " << mr[o] << " " << mc[o] << "\n";
      op[++opp] = {mr[o], mc[o], 0, 0, 3, o};
    }
  }
  sort(op + 1, op + opp + 1, [&](const O& x, const O& y) {
			       return x.t == y.t ? x.op < y.op : x.t > y.t;
			     });

  
  set<int> st;
  st.insert(0);

  auto getpos = [&](int p) {
		  auto it = st.upper_bound(p);
		  assert(it != st.begin());
		  assert(it == st.end() || *it != p);
		  --it;
		  return *it+1;
		};

  //cerr << "---\n";
  
  rep(i, 1, opp) {
    //cerr << op[i].t << " ";
    if(op[i].op == 1) {//insert
	tmp[op[i].pos] = query(1, op[i].r+1, 1, pb);
	//cerr << "i@ " << op[i].l << " " << op[i].r << " " << tmp[op[i].pos] << "\n";
	set0(1, op[i].l, op[i].r, 1, pb);
	st.insert(op[i].r);
    } else if(op[i].op == 3) {
      int pos = getpos(op[i].l);
      //cerr << "a@ " << pos << " " << op[i].l << "\n";
      add(1, pos, op[i].l, 1, 1, pb);
    } else if(op[i].op == 4) {
      ans[op[i].pos] = query(1, op[i].l, 1, pb);
      //cerr << "q@ " << op[i].l << " " << ans[op[i].pos] << "\n";
    } else if(op[i].op == 2) { //delete

      //cerr << "d@ " << op[i].l << " " << op[i].r << "\n";
      tmp2[op[i].pos] = query(1, op[i].r+1, 1, pb);
      int pos = getpos(op[i].l);
      add(1, pos, op[i].r, tmp2[op[i].pos], 1, pb);
      add(1, pos, op[i].l-1, -tmp[op[i].pos], 1, pb);
      //cerr << "[" << pos << ", " << op[i].r << "] += " << tmp2[op[i].pos] << "\n";
      //cerr << "[" << pos << ", " << op[i].l-1 << "] -= " << tmp[op[i].pos] << "\n";
      
    } else {
      st.erase(op[i].r);
    }
    //rep(j, 1, 7) cerr << query(1, j, 1, pb) << " \n"[j == 7];
  }
}


int main() {
  freopen("fence.in", "r", stdin);
  freopen("fence.out", "w", stdout);
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);

  memset(modi, -1, sizeof modi);

  cin >> k;
  rep(i, 1, k) {
    cin >> r1[i] >> c1[i] >> r2[i] >> c2[i];
    a[++pa] = r1[i];
    a[++pa] = r2[i];
    a[++pa] = r1[i]-1;
    b[++pb] = c1[i];
    b[++pb] = c2[i];
  }
  cin >> m;
  rep(i, 1, m) {
    cin >> mr[i] >> mc[i];
    a[++pa] = mr[i];
    b[++pb] = mc[i];
  }
  cin >> n;
  rep(i, 1, n) {
    cin >> qr[i] >> qc[i];
    a[++pa] = qr[i];
    b[++pb] = qc[i];
  }
  sort(a + 1, a + pa + 1), pa = unique(a + 1, a + pa + 1) - a - 1;
  sort(b + 1, b + pb + 1), pb = unique(b + 1, b + pb + 1) - b - 1;

  auto geta = [&](int x) { return lower_bound(a + 1, a + pa + 1, x) - a; };
  auto getb = [&](int x) { return lower_bound(b + 1, b + pb + 1, x) - b; };
  
  rep(i, 1, k) {
    r1[i] = geta(r1[i]);
    r2[i] = geta(r2[i]);
    c1[i] = getb(c1[i]);
    c2[i] = getb(c2[i]);
  }
  rep(i, 1, m) {
    mr[i] = geta(mr[i]);
    mc[i] = getb(mc[i]);
  }
  rep(i, 1, n) {
    qr[i] = geta(qr[i]);
    qc[i] = getb(qc[i]);
  }

  opp = 0;
  rep(i, 1, k) {
    op[++opp] = {r1[i], c1[i], c2[i], 1, 1, i};
    op[++opp] = {r2[i]+1, c1[i], c2[i], -1, 1, i};
  }
  rep(i, 1, n) op[++opp] = {qr[i], qc[i], 0, 0, 2, i};
  rep(i, 1, m) op[++opp] = {mr[i], mc[i], 0, 0, 3, i};
  
  s[0].emplace((int)1e9+5, 0);

  sort(op + 1, op + opp + 1, [&](const O& x, const O& y) {
			       return x.t == y.t ? x.op < y.op : x.t < y.t;
			     });

  auto find = [&](int b, int p) {
		auto it = s[b].lower_bound(mp(p, 0));
		assert(it != s[b].end());
		return it->se;
	      };
  
  rep(i, 1, opp) {
    int o = op[i].pos;
    //cerr << op[i].t << " ";
    if(op[i].op == 1) {
      if(op[i].x == 1) { //insert
	add(op[i].l, 1);
	add(op[i].r+1, -1);

	bel[o] = query(op[i].l);
	//cerr << "i@ " << op[i].l << " " << op[i].r << " " << bel[o] << "\n";
	
	assert(bel[o] > 0);
	
	s[bel[o]].emplace(c2[o], o);
	int f = find(bel[o]-1, op[i].l);
	adj[f].emplace_back(1, o);
      } else { //delete
	//cerr << "d@ " << op[i].l << " " << op[i].r << "\n";
	add(op[i].l, -1);
	add(op[i].r+1, 1);
	s[bel[o]].erase(mp(c2[o], o));
      }
    } else if(op[i].op == 2) { //niu
      qbel[o] = query(op[i].l);
      //cerr << "q@ " << op[i].l << " " << qbel[o] << "\n";
      int f = find(qbel[o], op[i].l);
      adj[f].emplace_back(2, o);
    } else {
      cbel[o] = query(op[i].l);
      //cerr << "c@ " << op[i].l << " " << cbel[o] << "\n";
      int f = find(cbel[o], op[i].l);
      adj[f].emplace_back(3, o);
    }
  }

  rep(i, 0, k) solve(i);
  rep(i, 1, n) cout << ans[i] << "\n";
  
  return 0;
}
