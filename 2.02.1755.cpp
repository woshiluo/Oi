#include <stdio.h>

int c[50];

int fac(int n){
	if(n==1) return 1;
	else if(n==2) return 1;
	else if(c[n]>0) return c[n];
	else {
		c[n]=fac(n-1)+fac(n-2);
		return  fac(n-1)+fac(n-2);
	}
}

int main(){
 int n;
 scanf("%d",&n);
 printf("%d",fac(n));
}
