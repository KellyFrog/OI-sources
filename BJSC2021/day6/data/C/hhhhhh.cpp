#include<bits/stdc++.h>
using namespace std;
#define ll long long

mt19937 rnd(time(NULL));

inline ll gcd(ll x,ll y) { return (!y)?x:gcd(y,x%y); }

int num[110];

inline ll gao()
{
	ll h1=rnd()%1000000000,h2=rnd()%1000000000;
	return h1*1000000000+h2+1;
}

int main()
{
	freopen("a40.in","w",stdout);
	ll a=gao(),b=gao();
	while (gcd(a,b)!=1) a=gao(),b=gao();
	//printf("%lld %lld\n",a,b);
	puts("1000000000000000000 999999999999999999");
	for (int i=1;i<=6;i++) num[i]=i,swap(num[i],num[rnd()%i+1]);
	for (int i=1;i<=6;i++) printf("%d ",num[i]);
	puts("");
	return 0;
}
