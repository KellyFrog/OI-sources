#include<bits/stdc++.h>
using namespace std;
#define ll long long

mt19937 rnd(time(NULL));

int num[110];

int main()
{
	freopen("a21.in","w",stdout);
	puts("5");
	for (int i=1;i<=5;i++)
	{
		puts("1000000000 5000");
		for (int i=1;i<=5000;i++) printf("%d %d\n",rnd()%1000000001,rnd()%1000000001);
		puts("5000");
		for (int i=1;i<=5000;i++) printf("%d %d\n",rnd()%1000000001,rnd()%1000000001);
	}
	return 0;
}
