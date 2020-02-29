#include <cstdio>
#include <cmath>
using namespace std;


void f(int n,char a,char b,char c){
	if(n==0) return ;
    f(n-1,a,c,b);
	printf("%d from %c to %c\n",n,a,c);
	f(n-1,b,a,c);
}

int main(){
	int n;
	char a='A',b='B',c='C';
	scanf("%d",&n);
	printf("%d\n",(int)pow(2,n)-1);
	f(n,a,b,c);
	return 0;
}
