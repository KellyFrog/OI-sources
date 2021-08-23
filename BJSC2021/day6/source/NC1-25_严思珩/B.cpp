#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<iostream>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
int n;
string a;
int kmp[2000005];
int t[25000005],cnt;
ll hash[2000005];
const ll base=13131,mod=998244353;
ll qpow[2000005];
ll ans;
ll check(int l,int r)
{
	return (hash[r]-(hash[l-1]*qpow[r-l+1])%mod+mod)%mod; 
}
int main()
{
	freopen("B.in","r",stdin);
	freopen("B.out","w",stdout);
	scanf("%d",&n);
	qpow[0]=1;
	for(int i=1;i<=n;i++) qpow[i]=(qpow[i-1]*base)%mod;
	cin>>a;
	a=' '+a;
	kmp[1]=0;
	for(int i=2;i<=n;i++)
	{
		int j=kmp[i-1];
		while(j!=0&&a[j+1]!=a[i]) j=kmp[j];
		if(a[j+1]==a[i]) j++;
		kmp[i]=j;
	}
	for(int i=1;i<=n;i++)
	{
		hash[i]=(hash[i-1]*base%mod+a[i]-'a')%mod;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=i;j<=n;j++)
		{
			int nw=0,l=cnt;
			bool flag=false;
			for(int k=1;k<=n;k++)
			{
				//if(i==j&&i==1) cout<<nw<<endl;
				while(nw!=0&&a[i+nw]!=a[k]) nw=kmp[nw];
				if(a[i+nw]==a[k]) nw++;
				if(nw==(j-i+1))
				{
					if(k<j)
					{
						flag=true;break;
					}
					t[++cnt]=k;
					nw=kmp[nw];
				}
			}
			if(flag) continue;
			
			l++;
			int r=cnt;
			//cout<<l<<" "<<r<<" "<<i<<" "<<j<<" "<<t[l]<<endl;
			for(int k=1;k<=n;k++)
			{
				if(t[l]+k>n) continue;
				ll maxx=0,minn=9e18;
				for(int o=l;o<=r;o++)
				{
					if(t[o]+k>n) continue;
					ll qwq=check(t[o]+1,t[o]+k);
					maxx=max(maxx,qwq);
					minn=min(minn,qwq);
				}
				if(maxx==minn) ans++;
			}
		}
	}
	printf("%lld\n",ans);
	return 0;
}
