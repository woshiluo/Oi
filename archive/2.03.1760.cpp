#include <stdio.h>

int a[1100000];

int sl(int n){
	if(n==1||n==2) return 1;
	if(a[n]>0) return a[n];
	else {
		a[n]=(sl(n-1)+sl(n-2))%1000;
		return a[n];
	}

	return 0;
}

int main(){
	int n;
	scanf("%d",&n);	
	for(int i=0;i<n;i++){
		int k;
		scanf("%d",&k);
		printf("%d\n",sl(k));
	}
}
