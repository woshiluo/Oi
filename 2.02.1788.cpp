#include <stdio.h>

int c[1100000];

long long pell(int n){
	if(n==1)return 1;
	else if(n==2)return 2;
	else if(c[n]>0) return c[n];
	else {
		c[n]=(2*pell(n-1)+pell(n-2))%32767;
		return c[n];
	}
}

int main(){
	int n;
	scanf("%d",&n);
	int a[n];
	for(int i=0;i<n;i++){
		scanf("%d",&a[i]);
		printf("%lld\n",pell(a[i])%32767);
	}

}
