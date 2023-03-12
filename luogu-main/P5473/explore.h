#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <bits/stdc++.h>

using namespace std;

#define MAX_N 200010
#define MAX_M 1000010
#define DEBUG 0

typedef struct {
int head[MAX_N], next[MAX_M << 1], to[MAX_M << 1], tot;
}	__bgggay666_adj;

class __bgggay233666233666233666 {
private:
	__bgggay666_adj e, f, d;
	int N, M, deg[MAX_N], cur_deg[MAX_N];
	int m_cnt, q_cnt, c_cnt;
	int m_lim, q_lim, c_lim;
	unsigned long long checksum;
	char mod[MAX_N], col[MAX_N], reported[MAX_M << 1];
	unsigned cur_encode;
	
public:
	#define CHECK_MOD 18436744073709551573ull

	unsigned password() {
		cur_encode = cur_encode * 65539u + 33333331u;
		return cur_encode >> 1;
	}

	void append(__bgggay666_adj* e, int a, int b) {
		++e->tot; e->next[e->tot] = e->head[a]; e->to[e->tot] = b; e->head[a] = e->tot;
	}

	void modify(int p) {
		if(!(0 <= p && p < N)) {
			printf("-1 %d\n", p);
			exit(0);
		}
		++m_cnt;
		if(m_cnt > m_lim) {
			printf("-2\n");
			exit(0);
		}
		mod[p] ^= 1;
		col[p] ^= 1;
		int k;
		for(k = f.head[p]; k; k = f.next[k]) col[f.to[k]] ^= 1;
	}
	int query(int p) {
		if(!(0 <= p && p < N)) {
			printf("-1 %d\n", p);
			exit(0);
		}
		++q_cnt;
		if(q_cnt > q_lim) {
			printf("-3\n");
			exit(0);
		}
		int c = col[p];
		int k;
		for(k = f.head[p]; k; k = f.next[k]) c ^= mod[f.to[k]];
		return c;
	}

	int verify(int p, int fa) {
		int k;
		for(k = f.head[p]; k; k = f.next[k])
			if(f.to[k] == fa && !reported[k])
				{reported[k] = 1; return 1;}
		return 0;
	}

	void report(int x, int y) {
		if(!(0 <= x && x < N)) {
			printf("-1 %d\n", x);
			exit(0);
		}
		if(!(0 <= y && y < N)) {
			printf("-1 %d\n", y);
			exit(0);
		}
		if(!verify(x, y) && !verify(y, x)) {
			printf("-4 %d %d\n", x, y);
			exit(0);
		} else {
			checksum += (x < y)
				? ((unsigned long long) (x) << 32 | y)
				: ((unsigned long long) (y) << 32 | x);
			if(checksum >= CHECK_MOD) checksum -= CHECK_MOD;
			--cur_deg[x]; --cur_deg[y];
		}
	}
	int check(int x) {
		if(!(0 <= x && x < N)) {
			printf("-1 %d\n", x);
			exit(0);
		}
		++c_cnt;
		if(c_cnt > c_lim) {
			printf("-5\n");
			exit(0);
		}
		return !cur_deg[x];
	}

	void init() {
		e.tot = 1;
		assert(scanf("%u", &cur_encode) == 1);
		assert(scanf("%d%d%d", &m_lim, &q_lim, &c_lim) == 3);
		m_lim ^= password();
		q_lim ^= password();
		c_lim ^= password();
		int i;
		assert(scanf("%d%d", &N, &M) == 2);
		N ^= password();
		M ^= password();

		for(i = 0; i < M; ++i) {
			int a, b;
			assert(scanf("%d%d", &a, &b) == 2);
			a ^= password();
			b ^= password();
			assert(a != b);
			assert(0 <= a && a < N);
			assert(0 <= b && b < N);
			++deg[a]; ++deg[b];
			append(&e, a, b);
			append(&e, b, a);
		}
		for(i = 0; i < N; ++i) {
			cur_deg[i] = deg[i];
			append(&d, deg[i], i);
		}
		int cur_max = N - 1;
		while(cur_max) {
			int p = -1, k;
			for(k = d.head[cur_max]; k; k = d.next[k]) {
				d.head[cur_max] = k;	
				if(cur_deg[d.to[k]] == cur_max) {
					p = d.to[k];
					break;
				}
			}
			if(p == -1) {--cur_max; continue;}
			static int q[MAX_N], dfn[MAX_N], timer;
			int l = 0, r = 0, s;
			dfn[q[r++] = p] = ++timer;
			while(l != r) {
				p = q[l++];
				for(k = e.head[p]; k; k = e.next[k]) {
					s = e.to[k];
					if(s != -1 && dfn[s] != timer) {
						dfn[q[r++] = s] = timer;
						e.to[k] = -1;
						e.to[k ^ 1] = -1;
						--cur_deg[p];
						--cur_deg[s];
						append(&f, s, p);
					}
				}
				if(cur_deg[p]) append(&d, cur_deg[p], p);
			}
		}
		for(i = 0; i < N; ++i) cur_deg[i] = deg[i];
		return ;
	}

	void finish() {
		for(int i = 0; i < N; ++i) if(cur_deg[i])
			{puts("-6");return ;}
		printf("0 %d %d %d %d %d %d\n", m_cnt, m_lim, q_cnt, q_lim, c_cnt, c_lim);
		return ;
	}

	int getN() {
		return N;
	}

	int getM() {
		return M;
	}
};

__bgggay233666233666233666 judge;

void modify (int p) {
	judge.modify(p);
	return ;
}
int query(int p) {
	return judge.query(p);
}
void report(int x, int y) {
	judge.report(x, y);
	return ;
}
int check(int x) {
	return judge.check(x);
}

void explore(int, int);

int main() {
	judge.init();
	explore(judge.getN(), judge.getM());
	judge.finish();
	return 0;
}

