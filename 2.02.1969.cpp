#include <stdio.h>
#include <stdlib.h>

double f(){
	char a[1100];
	scanf("%s",a);
	if(a[0]=='*') return f()*f();
	else if(a[0]=='+') return f()+f();
	else if(a[0]=='/') return f()/f();
	else if(a[0]=='-') return f()-f();
	else return atof(a);
}

int main(){
	printf("%lf\n",f());
}
