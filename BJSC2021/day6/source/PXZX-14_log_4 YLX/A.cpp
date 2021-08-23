#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include<bits/stdc++.h>
#define rep(a,b,c) for(register int a=(b);a<=(c);++a)
#define dow(a,b,c) for(register int a=(b);a>=(c);--a)
using namespace std;
const int MaxN=10000+5;
struct Vertex
{
	int px,py;
	int lef,rig,Gamma;
	bool typ;
	inline void ReadIn(void)
		{cin>>px>>py;}
	inline bool operator < (const Vertex& other) const
	{
		if(px==other.px)
			return (py<other.py);
		return (px<other.px);
	}
};
Vertex vt[MaxN],cur;
inline int Distance_x(const register int u,const register int v)
	{return (vt[u].Gamma+vt[v].Gamma);}
inline int Distance_y(const register int u,const register int v)
	{return (min(vt[u].rig,vt[v].rig)-max(vt[u].lef,vt[v].lef));}
int main()
{
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);
	ios::sync_with_stdio(false),cin.tie(NULL);
	register int T;
	cin>>T;
	while(T--)
	{
		register int n,m,q;
		cin>>m>>n;
		rep(i,1,n)
			vt[i].ReadIn();
		vt[++n]=(Vertex){0,0-1,true};
		vt[++n]=(Vertex){m,m+1,true};
		sort(vt+1,vt+n+1);
		cin>>q;
		while(q--)
		{
			cur.ReadIn();
			register int pos=(upper_bound(vt+1,vt+n+1,cur)-vt)-1;
			register int Record=0;
			dow(i,pos,1)
			{
				if(i==pos)
				{
					vt[i].lef=0,vt[i].rig=m;
					if((vt[i].Gamma=(cur.px-vt[i].px))==0) vt[i].Gamma=-(m+1);
					continue;
				}
				vt[i].lef=vt[i+1].lef,vt[i].rig=vt[i+1].rig;
				if(vt[i+1].py<=cur.py)
					vt[i].lef=max(vt[i].lef,vt[i+1].py);
				if(vt[i+1].py>=cur.py)
					vt[i].rig=min(vt[i].rig,vt[i+1].py);
				if((vt[i].Gamma=(cur.px-vt[i].px))==0) vt[i].Gamma=-(m+1);
			}
			rep(i,pos+1,n)
			{
				if(i==pos+1)
				{
					vt[i].lef=0,vt[i].rig=m;
					if((vt[i].Gamma=(vt[i].px-cur.px))==0) vt[i].Gamma=-(m+1);
					continue;
				}
				vt[i].lef=vt[i-1].lef,vt[i].rig=vt[i-1].rig;
				if(vt[i-1].py<=cur.py)
					vt[i].lef=max(vt[i].lef,vt[i-1].py);
				if(vt[i-1].py>=cur.py)
					vt[i].rig=min(vt[i].rig,vt[i-1].py);
				if((vt[i].Gamma=(vt[i].px-cur.px))==0) vt[i].Gamma=-(m+1);
			}
			register int pit=(pos+1);
			rep(i,1,pos)
			{
				if(vt[i].lef==cur.py||vt[i].rig==cur.py) continue;
				while((pit!=n)&&Distance_x(pit+1,i)<=Distance_y(pit+1,i)&&!
					(vt[pit+1].lef==cur.py||vt[pit+1].rig==cur.py))
					++pit;
				rep(j,max(pos+1,pit-2),min(n,pit+2))
					Record=max(Record,min(Distance_x(j,i),Distance_y(j,i)));
			}
			const register long long Answer=(long long)Record*Record;
			cout<<Answer<<endl;
		}
	}
	return 0;
}
