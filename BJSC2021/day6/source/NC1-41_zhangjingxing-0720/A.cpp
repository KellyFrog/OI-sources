#include<bits/stdc++.h>
//dengyaotriangle!
using namespace std;

const int maxn=5005;

int m,n,q;

struct poi{
	int x,y,ry,t;
}a[maxn*2],b[maxn*2];
int ans[maxn];

bool operator<(const poi&a,const poi&b){
	return a.x==b.x?a.t<b.t:a.x<b.x;
}	
bool cmp(const poi&a,const poi&b){
	return a.y<b.y;
}
int zl,zr;
int seq[maxn*2];
int rys[maxn*2];

void chkmx(int&a,int b){a=max(a,b);}

int main(){
	freopen("A.in","r",stdin);
	freopen("A.out","w",stdout);
	int t;
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&m,&n);
		for(int i=1;i<=n;i++){
			scanf("%d%d",&b[i].x,&b[i].y);
			b[i].t=-1;
		}
		scanf("%d",&q);
		for(int i=1;i<=q;i++)ans[i]=0;
		for(int i=1;i<=q;i++){
			scanf("%d%d",&b[i+n].x,&b[i+n].y);
			b[i+n].t=i;
		}
		if(n==0){
			for(int i=1;i<=q;i++){
				if(b[i].x&&b[i].x<m&&b[i].y&&b[i].y<m)ans[i]=m;
			}
		}
		for(int dir=0;dir<4;dir++){
			for(int i=1;i<=n+q;i++)a[i]=b[i];
			if(dir&1){
				for(int i=1;i<=n+q;i++)swap(a[i].x,a[i].y);
			}
			if(dir>>1){
				for(int i=1;i<=n+q;i++)a[i].x=m-a[i].x,a[i].y=m-a[i].y;
			}
			int h=n+q+2;
			a[n+q+1].x=m;a[n+q+1].y=0;a[n+q+1].t=-1;
			a[n+q+2].x=m;a[n+q+2].y=m;a[n+q+2].t=-1;
			sort(a+1,a+h+1,cmp);
			int h1=0;
			for(int i=1;i<=h;i++){
				if(a[i].t!=-1){
					++h1;rys[h1]=a[i].y;
					a[i].ry=h1;
				}
			}
			sort(a+1,a+h+1);
			//cerr<<dir<<endl;
			for(int i=1;i<=h;i++)if(a[i].t==-1&&a[i].x<m){
				int lmax=0,rmin=m;
				int ld=0;
				for(int i=1;i<=h1;i++)seq[i]=0;
				//cerr<<"P"<<a[i].x<<' '<<a[i].y<<endl;
				int slp=1,srp=h1;
				for(int j=i+1;j<=h;j++){
					if(a[j].x>a[i].x){
						//cerr<<a[j].x<<' '<<a[j].y<<endl;
						int d=a[j].x-a[i].x;
						if(rmin-lmax<d||j==h){
							for(int j=1;j<=h1;j++){
								if(seq[j]>0){
									chkmx(ans[seq[j]],ld);
								}
							}
							break;
						}
						if(a[j].t==-1){
							//cerr<<"x"<<a[j].y<<'/'<<lmax<<' '<<rmin<<endl;
							if(a[j].y<=a[i].y){
								lmax=max(lmax,a[j].y);
								while(slp<=h1&&rys[slp]<=a[j].y){
									if(seq[slp]>0){
										chkmx(ans[seq[slp]],d);
									}
									seq[slp]=-1;
									slp++;
								}
							}
							if(a[j].y>=a[i].y){
								rmin=min(rmin,a[j].y);
								while(srp>=1&&rys[srp]>=a[j].y){
									//cerr<<"?"<<srp<<endl;
									if(seq[srp]>0){
										chkmx(ans[seq[srp]],d);
									}
									seq[srp]=-1;
									srp--;
								}
							}
						}else if(a[j].x!=m&&a[j].y!=0&&a[j].y!=m){
							//cerr<<a[j].t<<'/'<<a[j].ry<<' '<<seq[a[j].ry]<<endl;
							if(seq[a[j].ry]==0){
								seq[a[j].ry]=a[j].t;
							}
						}
						ld=d;
						//for(int i=1;i<=h;i++)cerr<<seq[i]<<' ';
						//cerr<<endl;
					}
				}
			}
			//cerr<<"!!!"<<ans[1]<<endl;
		}
		for(int i=1;i<=q;i++)printf("%lld\n",ans[i]*(long long)ans[i]);
	}
	return 0;
}