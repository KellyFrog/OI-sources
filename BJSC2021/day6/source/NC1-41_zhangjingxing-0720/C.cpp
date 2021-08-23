#include<bits/stdc++.h>
//dengyaotriangle!
using namespace std;

long long a,b;

int f[6];

struct mat{
	long long v[8][8];
};

mat operator*(const mat&a,const mat&b){
	mat ret;
	for(int i=0;i<=7;i++){
		for(int j=0;j<=7;j++){
			ret.v[i][j]=0;
			for(int k=0;k<=7;k++){
				ret.v[i][j]+=a.v[i][k]*b.v[k][j];
			}
		}
	}
	return ret;
}
/*
typedef string mat;
mat operator*(const mat&a,const mat&b){return a+b;}
*/
mat rotr,rotu;
mat e;
mat qpw(mat bse,long long ex){
	mat ret=e;
	for(;ex;ex>>=1){
		if(ex&1)ret=ret*bse;
		bse=bse*bse;
	}
	return ret;
}
 
mat solve(long long a,long long b,mat r,mat u){
	if(b==0){
		return qpw(r,a);
	}
	return solve(b,a%b,qpw(r,a/b)*u,r);
}
int main(){
	freopen("C.in","r",stdin);
	freopen("C.out","w",stdout);
	scanf("%lld%lld",&a,&b);
	for(int i=0;i<6;i++){
		scanf("%d",f+i);
	}
	rotr.v[4][3]=1;rotr.v[3][1]=1;rotr.v[1][2]=1;rotr.v[2][4]=1;rotr.v[0][0]=1;rotr.v[5][5]=1;rotr.v[4][6]=1;rotr.v[6][7]=1;rotr.v[7][7]=1;
	rotu.v[4][0]=1;rotu.v[0][1]=1;rotu.v[1][5]=1;rotu.v[5][4]=1;rotu.v[3][3]=1;rotu.v[2][2]=1;rotu.v[4][6]=1;rotu.v[6][7]=1;rotu.v[7][7]=1;
	for(int i=0;i<=7;i++)e.v[i][i]=1;
	//rotr="R";rotu="U";
	mat ret=solve(a,b,rotr,rotu);
	//cerr<<ret;
	//mat ret=rotu*rotr*rotu*rotr*rotu;
	long long ans=0;
	for(int i=0;i<6;i++)ans+=f[i]*ret.v[i][7];
	printf("%lld",ans);
	return 0;
}