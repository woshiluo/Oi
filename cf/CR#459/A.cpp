#include <cstdio>
using namespace std;

long long n;
long long a[11000];
bool x[110000];

int main(){
	scanf("%d",&n);
	a[1]=a[2]=1;
	x[1]=true;
	for(int i=3;i<=20;i++){
		a[i]=a[i-1]+a[i-2];
		x[a[i]]=true;
	}
	for(int i=1;i<=n;i++){
		if(x[i]) printf("O");
		else printf("o");
	}
	return 0;
}
