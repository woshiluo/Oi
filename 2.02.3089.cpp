#include <cstdio>
using namespace std;

int a[45],i=0,cnt;

void f(int less){
	if(less==0){cnt++; return ;}
	for(int i=1;i<=2;i++){
		if(less-i>=0) f(less-i);
	}
}

int main(){
	while(1){
		if(scanf("%d",&a[i])==EOF)	break;
		f(a[i]);
		printf("%d\n",cnt);
		cnt=0;
		i++;
	}
}
