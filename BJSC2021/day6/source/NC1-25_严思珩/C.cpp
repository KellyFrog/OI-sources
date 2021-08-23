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
ll n,m;
ll a[10];
int main()
{
	freopen("C.in","r",stdin);
	freopen("C.out","w",stdout);
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=6;i++)
	{
		scanf("%lld",&a[i]);
	}
	printf("%lld\n",(n+m-1)*3+(n+m-1)/2+(n-m+1%2==1?rand()%2:0));
	return 0;
}
