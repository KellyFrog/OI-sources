#include <bits/stdc++.h>
using namespace std;

# define Rep(i,a,b) for(int i=a;i<=b;i++)
# define _Rep(i,a,b) for(int i=a;i>=b;i--)
# define RepG(i,u) for(int i=head[u];~i;i=e[i].next)

typedef long long ll;

const int N=505;

template<typename T> void read(T &x){
   x=0;int f=1;
   char c=getchar();
   for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
   for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-'0';
    x*=f;
}

int t,n,m,q;

struct node{
	int x,y;	
}a[N];
int sum[N][N];

int getsum(int x1,int y1,int x2,int y2){
	if(x1>x2||y1>y2)return 0;
	return sum[x2][y2]-sum[x1-1][y2]-sum[x2][y1-1]+sum[x1-1][y1-1];	
}

int main()
{
	freopen("testdata.in","r",stdin);
	freopen("test2.out","w",stdout);
	read(t);
	while(t--){
		memset(sum,0,sizeof(sum));
		read(m),read(n);
		Rep(i,1,n)read(a[i].x),read(a[i].y),sum[a[i].x][a[i].y]++;
		Rep(i,0,m)
			Rep(j,0,m)
				sum[i][j]+=(j?sum[i][j-1]:0)+(i?sum[i-1][j]:0)-((i&&j)?sum[i-1][j-1]:0);
		read(q);
		while(q--){
			int x,y;
			read(x),read(y);
			ll ans=0;
			Rep(l,0,x-1)
				Rep(u,0,y-1)
					Rep(len,2,m)
						if(l+len>x&&u+len>y&&l+len<=m&&u+len<=m)
							if(!getsum(l+1,u+1,l+len-1,u+len-1)) 
								ans=max(ans,1ll*len*len);
			printf("%lld\n",ans);
		}
	}
	return 0;
}
/*
1
5 5
1 4
2 1
3 2
4 1
4 4
3
3 1
2 3
4 3

*/
