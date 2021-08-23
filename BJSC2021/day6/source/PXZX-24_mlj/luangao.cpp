#include <cstdio>
#include <iostream>
#include <cstdio>
#define LL long long
using namespace std;
LL read(){
	LL x=0,k=1;char ch=getchar();
	while('0'>ch || ch>'9'){if(ch=='-')k=-1;ch=getchar();}
	while('0'<=ch && ch<='9'){x=x*10+(ch^48);ch=getchar();}
	return x*k;
}
LL A,B;
int a[100010];
int dis[100010];
int main(){
	A=read();B=read();
	if(A>B)swap(A,B);
	a[0]=1;
	for(int i=1;i<=A;i++){
		a[i]=int((B*i+A-1)/A);
		cout<<a[i]-a[i-1]+1<<" "<<i-dis[a[i]-a[i-1]+1]<<endl;
		dis[a[i]-a[i-1]+1]=i;
	}
	return 0;
} 
