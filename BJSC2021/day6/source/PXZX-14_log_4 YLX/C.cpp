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
using namespace std;
char a[7];
int main()
{
	freopen("C.in","r",stdin);
	freopen("C.out","w",stdout);
	ios::sync_with_stdio(false),cin.tie(NULL);
	register int n,m,k,K=20000000;
	cin>>n>>m,k=(n+m-2);
	cin>>a[0],a[0]-=48;
	cin>>a[1],a[1]-=48;
	cin>>a[2],a[2]-=48;
	cin>>a[3],a[3]-=48;
	cin>>a[4],a[4]-=48;
	cin>>a[5],a[5]-=48;
	register int Sum=(n-m);
	register long long Answer=a[4];
	const int Quotient=(k/20000000),Remainder=(k%20000000);
	register int Record;
	for(register int I=0;I<=Quotient;++I)
	{
		if(I)
			K=20000000;
		else
			K=Remainder;
		Record=0;
		if(K==20000000)
		{
			register int KK=312500;
			while(KK--)
			{
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
				if(Sum<=0)
					Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
				else
					Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
				Record+=a[4];
			}
		}
		else while(K--)
		{
			if(Sum<=0)
				Sum+=n,a[6]=a[1],a[1]=a[0],a[0]=a[4],a[4]=a[5],a[5]=a[6];
			else
				Sum-=m,a[6]=a[2],a[2]=a[1],a[1]=a[3],a[3]=a[4],a[4]=a[6];
			Record+=a[4];
		}
		Answer+=Record;
	}
	cout<<Answer<<endl;
	return 0;
}
