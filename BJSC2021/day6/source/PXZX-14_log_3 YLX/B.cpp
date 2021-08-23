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
const int MaxN=5000+5,Sig=26,Bit=14,Inf=(1<<30)-1;
char str[MaxN];
inline int CharIndex(const register char ch)
	{return (int)(ch-'a'+1);}
int Suf[MaxN],Rnk[MaxN],Old[MaxN];
int idx[MaxN],rec[MaxN],cnt[MaxN];
inline bool Compare(const register int px,const register int py,const register int lev)
	{return (Old[px]==Old[py])&&(Old[px+lev]==Old[py+lev]);}
inline void GetSuffixArray(const register int len)
{
	register int siz=(Sig+1),pit=0;
	rep(i,1,len) ++cnt[Rnk[i]=CharIndex(str[i])];
	rep(i,1,siz) cnt[i]+=cnt[i-1];
	dow(i,len,1) Suf[cnt[Rnk[i]]--]=i;
	for(register int lev=1;lev<=len;lev=(lev<<1),siz=pit)
	{
		pit=0; dow(i,len,len-lev+1) idx[++pit]=i;
		rep(i,1,len) if(Suf[i]>=lev+1) idx[++pit]=(Suf[i]-lev);
		rep(i,1,siz) cnt[i]=0;
		rep(i,1,len) ++cnt[rec[i]=Rnk[idx[i]]];
		rep(i,1,siz) cnt[i]+=cnt[i-1];
		dow(i,len,1) Suf[cnt[rec[i]]--]=idx[i];
		rep(i,1,len) Old[i]=Rnk[i];
		pit=0; rep(i,1,len) Rnk[Suf[i]]=Compare(Suf[i],Suf[i-1],lev)?(pit):(++pit);
	}
}
int Hei[MaxN];
inline void GetHeightArray(const register int len)
{
	register int cur=0;
	rep(i,1,len)
	{
		if(cur>=1) --cur;
		while(str[i+cur]==str[Suf[Rnk[i]-1]+cur]) ++cur;
		Hei[Rnk[i]]=cur;
	}
}
struct ST_List
{
	int Log2[MaxN],Min[MaxN][Bit+1];
	inline void Initalize(const register int len)
	{
		Log2[0]=-1;
		rep(i,1,len)
			Log2[i]=Log2[i>>1]+1;
		rep(i,1,len)
			Min[i][0]=Hei[i];
		rep(lv,1,Bit)
			rep(i,1,len-(1<<lv)+1)
				Min[i][lv]=min(Min[i][lv-1],Min[i+(1<<(lv-1))][lv-1]);
	}
	inline int Query(const register int beg,const register int end)
	{
		if(beg>end) return Inf;
		register int lv=Log2[end-beg+1];
		return min(Min[beg][lv],Min[end-(1<<lv)+1][lv]);
	}
};
ST_List St;
inline int LargestCommonPrefix(const register int px,const register int py)
	{return St.Query(min(Rnk[px],Rnk[py])+1,max(Rnk[px],Rnk[py]));}
int Occurr[MaxN],Cum[MaxN];
inline void FindEveryOccurrence(const register int len,const register int px,const register int py)
{
	Occurr[Occurr[0]=1]=px;
	register int pit=Rnk[px];
	while((pit!=len)&&LargestCommonPrefix(Suf[pit+1],px)>=(py-px+1))
		Occurr[++Occurr[0]]=Suf[++pit];
	pit=Rnk[px];
	while((pit!=1)&&LargestCommonPrefix(Suf[pit-1],px)>=(py-px+1))
		Occurr[++Occurr[0]]=Suf[--pit];
	sort(Occurr+1,Occurr+Occurr[0]+1);
}
inline void Initalize(register int& len)
{
	cin>>len>>(str+1);
	GetSuffixArray(len),GetHeightArray(len);
	St.Initalize(len);
}
bitset<MaxN> Bitset[MaxN];
int main()
{
	freopen("B.in","r",stdin);
	freopen("B.out","w",stdout);
	ios::sync_with_stdio(false),cin.tie(NULL);
	register int n,k;
	Initalize(n);
	register long long Answer=0;
	rep(i,1,n)
		rep(j,i,n)
		{
			if(Bitset[i][j]) continue;
			FindEveryOccurrence(n,i,j);
			rep(l,1,Occurr[0])
			{
				if(l==1)
					Cum[1]=(n-(Occurr[1]+(j-i)));
				else
					Cum[l]=min(Cum[l-1],LargestCommonPrefix(Occurr[l-1]+(j-i+1),Occurr[l]+(j-i+1)));
				if(l==Occurr[0])
					Answer+=Cum[l];
				else
					Answer+=max(0,Cum[l]-(n-(Occurr[l+1]+(j-i))));
				Bitset[Occurr[l]][Occurr[l]+(j-i)]=true;
			}
		}
	cout<<Answer<<endl;
	return 0;
}
