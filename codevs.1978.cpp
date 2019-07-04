#include <cstdio>
using namespace std;

/*int  f(int n){
	if(n==1) return 1;
	else if(n==2) return 1;
	else return f(n-1)+f(n-2);
}*/
int a[41];
int main(){
	int n;
	scanf("%d",&n);
	a[1]=a[2]=1;
	for(int i=3;i<=40;i++) a[i]=a[i-1]+a[i-2];
	printf("%d",a[n]);
}
