#include <bits/stdc++.h>
using namespace std;

# define Rep(i,a,b) for(int i=a;i<=b;i++)
# define _Rep(i,a,b) for(int i=a;i>=b;i--)
# define RepG(i,u) for(int i=head[u];~i;i=e[i].next)

typedef long long ll;

const int N=1e5+5;

template<typename T> void read(T &x){
   x=0;int f=1;
   char c=getchar();
   for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
   for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-'0';
    x*=f;
}

int t,n,m,q;

int main()
{
	srand(time(0));
	t=2;
	printf("%d\n",t);
	while(t--){
		n=1000,m=30,q=10;
		printf("%d %d\n",m,n);
		Rep(i,1,n)printf("%d %d\n",rand()%(m+1),rand()%(m+1));
		printf("%d\n",q);
		while(q--)printf("%d %d\n",rand()%(m+1),rand()%(m+1));
	}
	return 0;
}
