#include<cstdio>
#include<cmath>

const double pi=acos(-1);
int n,r,m;
double x;

int gcd(int a,int b){return b?gcd(b,a%b):a;}

int main(){
	scanf("%d%d",&n,&r);
	x=(double)( (r*sin(pi/(n)))/(1-sin(pi/n)) );
    printf("%.6lf",x);
}
