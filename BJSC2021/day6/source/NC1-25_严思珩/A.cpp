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
#pragma GCC optimize(2)
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<iostream>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#define int ll
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
int T;
int m,n;
int q;
int x[5005],y[5005];
signed main()
{
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&m,&n);
		for(int i=1;i<=n;i++)
		{
			scanf("%d%d",&x[i],&y[i]);
		}
		scanf("%d",&q);
		for(int l=1;l<=q;l++)
		{
			int u,v;
			ll ans=0;
			scanf("%d%d",&u,&v);
			for(int i=1;i<=n;i++)
			{
				for(int j=i+1;j<=n;j++)
				{
					//if(!(max(x[i],x[j])>u&&min(x[i],x[j])<u&&max(y[i],y[j])>v&&min(y[i],y[j])<v)) continue;
					//cout<<i<<" "<<j<<" qwq"<<endl;
					if(abs(x[i]-x[j])>=abs(y[i]-y[j]))
					{
						if(!(max(x[i],x[j])>u&&min(x[i],x[j])<u)) continue;
						int cnt=0,maxx=0,minn=m;
						for(int k=1;k<=n;k++)
						{
							if(x[k]<=min(x[i],x[j])||x[k]>=max(x[i],x[j])) continue;
							if(y[k]>min(y[i],y[j])) minn=min(y[k],minn);
							if(y[k]<max(y[i],y[j])) maxx=max(y[k],maxx);
						}
						//cout<<maxx<<" "<<minn<<endl;
						if(minn-maxx>=abs(x[i]-x[j])&&(max(x[i],x[j])>u&&min(x[i],x[j])<u&&max(maxx,minn)>v&&min(maxx,minn)<v)) ans=max(ans,1ll*(ll)(abs(x[i]-x[j])*(abs(x[i]-x[j]))));
					}
					else
					{
						int cnt=0,maxx=0,minn=m;
						if(!(max(y[i],y[j])>v&&min(y[i],y[j])<v)) continue;
						for(int k=1;k<=n;k++)
						{
							if(y[k]<=min(y[i],y[j])||y[k]>=max(y[i],y[j])) continue;
							if(x[k]>min(x[i],x[j])) minn=min(x[k],minn);
							if(x[k]<max(x[i],x[j])) maxx=max(x[k],maxx);
						}
						if(minn-maxx>=abs(y[i]-y[j])&&(max(maxx,minn)>u&&min(maxx,minn)<u&&max(y[i],y[j])>v&&min(y[i],y[j])<v)) ans=max(ans,1ll*(ll)(abs(y[i]-y[j])*(abs(y[i]-y[j]))));
					}
				}
			}
			printf("%lld\n",ans);
		}
	}
	return 0;
}
