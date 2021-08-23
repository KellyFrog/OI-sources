#include <bits/stdc++.h>
using namespace std;

# define Rep(i,a,b) for(int i=a;i<=b;i++)
# define _Rep(i,a,b) for(int i=a;i>=b;i--)
# define RepG(i,u) for(int i=head[u];~i;i=e[i].next)

typedef long long ll;

const int N=305;

template<typename T> void read(T &x){
   x=0;int f=1;
   char c=getchar();
   for(;!isdigit(c);c=getchar())if(c=='-')f=-1;
   for(;isdigit(c);c=getchar())x=(x<<1)+(x<<3)+c-'0';
    x*=f;
}

ll A,B,X,Y;
ll ans=0;
double k;
int f,u,r,l,d,b;
int tf,tu,tr,tl,td,tb;

int main(){
	freopen("C.in","r",stdin);
	freopen("C.out","w",stdout);
	read(A),read(B);
	read(b),read(u),read(r),read(l),read(d),read(f);
	if(A==1&&B==1)return printf("%d\n",d),0;
	k=(1.0*B/A);
	X=0,Y=0;
	ans+=d;
	A--,B--;
	while(true){
		if(k*(double)(X+1)>=Y&&k*(double)(X+1)<=Y+1){
			X++;
			tu=u,tr=r,td=d,tl=l;
			u=tl,r=tu,d=tr,l=td;
			ans+=d;
		}
		else{
			Y++;
			tu=u,tf=f,td=d,tb=b;
			u=tb,f=tu,d=tf,b=td;
			ans+=d;
		}
		if(X==A&&Y==B)
			break;
	}
	printf("%lld\n",ans);
	return 0;
}
