#include "jumps.h"

#include<bits/stdc++.h>
#define ui unsigned int
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(i=(a);i<=(b);++i)
#define per(i,a,b) for(i=(a);i>=(b);--i)
#define REP(i,a,b) for(i=(a);i< (b);++i)
#define PER(i,a,b) for(i=(a);i> (b);--i)
#define ERR(...) std::fprintf(stderr,__VA_ARGS__)
namespace ya{
	template<class T>inline void cmn(T &x,const T &a){if(a<x)x=a;}
	template<class T>inline void cmx(T &x,const T &a){if(x<a)x=a;}
	template<class T>inline bool bmn(T &x,const T &a){if(a<x){x=a;return true;}else return false;}
	template<class T>inline bool bmx(T &x,const T &a){if(x<a){x=a;return true;}else return false;}
}
//sol.cpp
namespace imalyd{
	const int MAXN=200005,K=17;
	int Stk[MAXN],Lg[MAXN],ST[K+1][MAXN],*H=ST[0],MX[K+1][MAXN],*Mx=MX[0],MN[K+1][MAXN],*Mn=MN[0];
	inline void init(const int &N,const std::vector<int> &h){
		const int INF=N+1;

		int i;
		REP(i,2,N)Lg[i]=Lg[i>>1]+1;
		REP(i,0,N)H[i]=h[i];
		int k,*S0(H),*S1;
		REP(k,0,K){
			S1=ST[k+1];
			REP(i,(2<<k)-1,N)S1[i]=std::max(S0[i],S0[i-(1<<k)]);
			S0=S1;
		}

		int tp(0);
		*Stk=INF;
		REP(i,0,N){
			k=H[i];
			while(Stk[tp]<k)--tp;
			if(tp)Mx[k]=Stk[tp];
			Stk[++tp]=k;
		}

		tp=0;
		per(i,N-1,0){
			k=H[i];
			while(Stk[tp]<k)--tp;
			if(tp)ya::cmx(Mx[k],Mn[k]=Stk[tp]);else Mn[k]=INF;
			Stk[++tp]=k;
		}
		
		rep(i,1,N)if(!Mx[i])Mx[i]=INF;
		(S0=Mx)[INF]=INF;
		REP(k,0,K){
			S1=MX[k+1];
			rep(i,1,INF)S1[i]=S0[S0[i]];
			S0=S1;
		}
		
		(S0=Mn)[INF]=INF;
		REP(k,0,K){
			S1=MN[k+1];
			rep(i,1,INF)S1[i]=S0[S0[i]];
			S0=S1;
		}
	}
	inline int qmx(const int &a,const int &b){
		int k(Lg[b-a+1]),*Sk(ST[k]);
		return std::max(Sk[a+(1<<k)-1],Sk[b]);
	}
	inline int query(const int &A,int B,const int &C,int D){
		int M(qmx(B,C-1));
		if(M>(D=qmx(C,D)))return -1;
		//ERR("M=%d D=%d\n",M,D);

		int k,m(0),t;
		per(k,K,0)if(B-A+1>=(1<<k)&&(t=ST[k][B])<=D){ya::cmx(m,t);B-=(1<<k);}
		//ERR("m=%d\n",m);
		
		if(m>=M)return 1;

		int Ans1(0);
		per(k,K,0)if(MX[k][m]<M){m=MX[k][m];Ans1|=(1<<k);}
		//ERR("m=%d Mx[m]=%d\n",m,Mx[m]);
		//if(Mx[m]>=M&&Mx[m]<=D)ERR("%d + 2\n",Ans1);
		if(Mx[m]>=M&&Mx[m]<=D)return Ans1+2;

		int Ans2(0);
		per(k,K,0)if(MN[k][m]<M){m=MN[k][m];Ans2|=(1<<k);}
		//ERR("%d + %d + 2\n",Ans1,Ans2);
		return Ans1+Ans2+2;
	}
};
void init(int N, std::vector<int> H) {
	imalyd::init(N,H);
}
int minimum_jumps(int A, int B, int C, int D) {
	return imalyd::query(A,B,C,D);
}
