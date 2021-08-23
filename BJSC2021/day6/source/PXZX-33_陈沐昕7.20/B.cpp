#include <bits/stdc++.h>
using namespace std;

# define Rep(i,a,b) for(int i=a;i<=b;i++)
# define _Rep(i,a,b) for(int i=a;i>=b;i--)
# define RepG(i,u) for(int i=head[u];~i;i=e[i].next)

typedef long long ll;

const int N=305;
const int base=19841989;

template<typename T> void read(T &x){
   x=0;int f=1;
   char c=getchar();
   for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
   for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-'0';
    x*=f;
}

# define ull unsigned long long

int n;
char s[N];
ull poww[N],ha[N];
map<pair<ull,ull>,bool> var;
int ans;

ull getha(int l,int r){
	l--;
	return ha[r]-poww[r-l]*ha[l];	
}

int main()
{
	freopen("B.in","r",stdin);
	freopen("B.out","w",stdout);
	read(n);
	scanf("%s",s+1);
	poww[0]=1;
	Rep(i,1,n)poww[i]=poww[i-1]*base;
	Rep(i,1,n)ha[i]=ha[i-1]*base+s[i];
	Rep(i,1,n)
		Rep(j,1,i)
			Rep(k,i+1,n){
				if(var[make_pair(getha(j,i),getha(i+1,k))])continue;
				int cnt1=0,cnt2=0;
				Rep(s,1,n-(k-i+1)+1){
					int t=s+k-i;
					if(getha(s,s+j-i)==getha(j,i))cnt1++;
					if(getha(s,t)==getha(i,k))cnt2++;
				}
				if(cnt1==cnt2)ans++;
				var[make_pair(getha(j,i),getha(i+1,k))]=true; 
			}
	printf("%d\n",ans);
	return 0;
}
