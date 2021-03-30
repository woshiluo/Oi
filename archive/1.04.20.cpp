#include <stdio.h>
#include <math.h>
int main(){
	double a,b,c,x1,x2;
	scanf("%lf %lf %lf",&a,&b,&c);
	if(b*b-4*a*c==0){
		x1 = (-b + sqrt(b*b-4*a*c))/2/a;
		printf("x1=x2=%.5lf\n",x1);
	}
	if(b*b-4*a*c>0){
		x1 = (-b + sqrt(b*b-4*a*c))/2/a;
		x2 = (-b - sqrt(b*b-4*a*c))/2/a;
		printf("x1=%.5lf;x2=%.5lf\n",x1,x2);
	}
	if(b*b-4*a*c<0){
		double x,y;
		x= -b/2/a;
		if(x==0) x=0;
		y= sqrt(4*a*c-b*b) / (2*a);
		if(y==0) y=0;
		printf("x1=%.5lf+%.5lfi;x2=%.5lf-%.5lfi\n",x,y,x,y);
	}
	return 0;
}
